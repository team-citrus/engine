#ifndef _WIN32

#include <unistd.h>
#define MAIN main(int argc, char const **argv)

#else 

#include <windows.h>
#define MAIN APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) // We have to use the WinMain bullshit for GUI init in windows.

#endif

// main.cpp is an exception to the no STL rule
#include <chrono>
#include <mutex>

#ifdef __STDC_NO_THREADS__

#error The Citrus Engine requires threads.h

#endif

#include <threads.h>
#include <ctime>
#include <csetjmp>
#include <cstdlib>
#include <csignal>
#include <cstdio>
#include <cpuid.h>
#include <X11/Xlib.h>
#include "core/mem.hpp"
#include "core/mem_int.hpp"
#include "core/Main.hpp"
#include "core/scene.hpp"
#include "core/scene_int.hpp"
#include "core/workQueue.hpp"
#include "core/log.hpp"
#include "core/errno.hpp"
#include "core/crash.hpp"
#include "core/rng.hpp"
#include "core/jobsys.hpp"
#include "graphics/vkInit.hpp"
#include "graphics/initGL.hpp"

#define getTimeInMils() std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()

using namespace engine;
using namespace internals;

bool internals::usingVulkan;
int internals::frameRate;
jmp_buf internals::buf

size_t internals::frameDelta;
size_t internals::frameDur;

size_t internals::physics::physicsDelta;
size_t internals::physics::physicsDur;

thrd_t internals::render;
thrd_t internals::phys;
thrd_t internals::mix;
thrd_t internals::gameplay;

// Probably the most commonly overriden weak function.
WEAK NO_INLINE extern void crashHandler();

void waitms(size_t mils)
{
	#ifndef _WIN32

	timespec t = { 0, (long)(mils * 1000000l) };
	nanosleep(&t, NULL); // Doesn't matter if we don't sleep long enough, waitms() is only to make sure we yield to the OS

	#else 

	Sleep(mils); // Rare instance of the Windows version being easier than the POSIX version

	#endif
}

#ifndef _WIN32

#define SIGARGS int sig, siginfo_t *info, void *ucontext

#else

#define SIGARGS int sig

#endif

void sigsev(SIGARGS)
{
	#ifndef _WIN32

	#ifdef _DEBUG_

	engine::log(STRINGIFY(Segfault handler), "Segfault triggered, dumping memory pool.");
	engine::log(STRINGIFY(Segfault handler), "Memory pool size: %zu", engine::internals::pool.size);
	engine::log(STRINGIFY(Segfault handler), "Pool limit: %zu", engine::internals::pool.limit);
	engine::log(STRINGIFY(Segfault handler), "Limit exceeded: %p", engine::internals::pool.limitExceeded);
	engine::log(STRINGIFY(Segfault handler), "Offending address: %p", info->si_addr);
	engine::log(STRINGIFY(Segfault handler), "Dumping core now.");

	FILE *poolf = fopen("poolclass", "w");
	FILE *core = fopen("core", "wb");

	fwrite(&engine::internals::pool, sizeof(engine::internals::Pool), 1, poolf);
	fwrite(engine::internals::start, 1, engine::internals::pool.size, core);

	engine::log(STRINGIFY(Segfault handler), "Core dump complete.");

	exit(SEGFAULT);

	#else

	engine::log(STRINGIFY(Segfault handler), "Segmentation fault!");
	exit(SEGFAULT);

	#else

	#ifdef _DEBUG_

	engine::log(STRINGIFY(Segfault handler), "Segfault triggered, dumping memory pool.");
	engine::log(STRINGIFY(Segfault handler), "Memory pool size: %zu", engine::internals::pool.size);
	engine::log(STRINGIFY(Segfault handler), "Pool limit: %zu", engine::internals::pool.limit);
	engine::log(STRINGIFY(Segfault handler), "Limit exceeded: %p", engine::internals::pool.limitExceeded);
	engine::log(STRINGIFY(Segfault handler), "Offending address unknown.");
	engine::log(STRINGIFY(Segfault handler), "Dumping core now.");

	FILE *poolf = fopen("poolclass", "w");
	FILE *core = fopen("core", "wb");

	fwrite(&engine::internals::pool, sizeof(engine::internals::Pool), 1, poolf);
	fwrite(engine::internals::start, 1, engine::internals::pool.size, core);

	engine::log(STRINGIFY(Segfault handler), "Core dump complete.");

	exit(SEGFAULT);

	#else

	engine::log(STRINGIFY(Segfault handler), "Segmentation fault!");
	exit(SEGFAULT);

	#endif
}

void sigill(SIGARGS)
{
	engine::log(STRINGIFY(Illegal instruction handler), "An illegal instruction has been triggered!");
	#if defined(_DEBUG_) && !defined(_WIN32)

	engine::log(STRINGIFY(Illegal instruction handler), "Offending address: %p", info->si_addr);

	#endif
	
	if(!__builtin_cpu_supports("sse4.2")
		#ifdef _MAVX_
		
		|| !__builtin_cpu_supports("avx")
		
		#if _MAVX_ == 2

		|| !!__builtin_cpu_supports("avx2")
		
		#endif
		
		#endif
	) // TODO: Turn those checks into a function
	{
		engine::log(STRINGIFY(Illegal instruction handler), "CPU does not support necessary instruction sets!");

		// TODO: Dump CPUID
		// TODO: Dump build flags

		exit(INVALID_CPU);
	}
	else
	{
		exit(SIG_ILLEGAL_INSTRUCTION);
	}
}

// Initialize signals, very different depending on build types and operating systems
static inline void initSigs()
{
	#ifndef _WIN32

	sigaction ssigsev;
	sigaction ssigill;
	ssigsev.sa_sigaction = sigsev;
	ssigsev.sa_mask = 0;
	ssigsev.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &ssigsev, NULL);
	ssigill.sa_sigaction = sigill;
	ssigill.sa_mask = 0;
	ssigill.sa_flags = SA_SIGINFO;
	sigaction(SIGILL, &ssigill, NULL);

	// TODO: Other signals

	#else

	signal(SIGSEGV, sigsev);
	signal(SIGILL, sigsev);

	// TODO: Other signals

	#endif
}

int MAIN
{
	// Initalize everything
	crashHandler();

	initMainRNG();

	initLogging();
	pool = Pool();
	initSigs();

	jobsBeingAccessed.store(false);
	jobs = priority = asap = Vector<Job>();
	executing = Map<JobPtr, std::thread::id>();
	initJobSystem();

	// TODO: Implement settings

	Vulkan::vkLoad();

	// TODO: Add GUI init, and splash screen stuff, splash screen should probably be on a different thread.

	// TODO: Load main scene

	while(true) // Outer loop is run each scene
	{
		// Physics runs on it's own internal timings, and executes some gameplay code
		thrd_create(&internals::phys, internals::physmain, NULL);

		while(true) // Inner loop is run each frame
		{
			size_t frameStart = getTimeInMils();

			// Internally, each thread will handle synchronization
			// They should execute in the following order:
			// Physics  ->        -> Physics
			// Gameplay -> Render
			//          -> Mix
			// Physics locks Gameplay and render and mix
			// Gameplay locks render and mix and physics
			// If gameplay executes at the same time as render and mix bad things will happen

			// TODO: Optimize this
			// render will automatically create and join mix 

			thrd_create(&internals::gameplay, internals::gameplayM, NULL);
			thrd_create(&internals::render, internals::draw, NULL);

			thrd_join(internals::gameplay, NULL);
			thrd_join(internals::render, NULL);

			if(internals::loadNecesary) break; // If a new scene needs to load, stop handling frames.

			// Handle the waits
			internals::frameDur = getTimeInMils() - frameStart;
			waitms(
				// Approximate the time between frames and wait for that duration
				(frameDelta = (1000 - (frameDur * internals::frameRate))/internals::frameRate)
			);
		}

		thrd_join(internals::phys, NULL); // Physics will load the new scene and then terminate.
	}

	return 0;
}
