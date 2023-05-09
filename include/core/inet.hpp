/*
*   name: include/core/inet.hpp
*   origin: Citrus Engine
*   purpose: The header for the network system
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#ifndef CITRUS_ENGINE_NEWORKING_HPP__
#define CITRUS_ENGINE_NEWORKING_HPP__

#ifdef _WIN32

#include <winsock2.h>

#else

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <fcntl.h>

#endif

#include <cstdlib>
#include <cstdint>
#include "core/errno.hpp"

#ifdef CITRUS_ENGINE_SERVER_SOCKETS

#include "core/jobsys.hpp"

#endif

namespace engine
{
	// TODO: Socket reference counting

	enum SocketTypes
	{
		TCP = 1, UDP = 2, TCP6 = 0x81, UDP6 = 0x82
	};

	class Socket
	{
		SocketTypes type;

		#ifdef _WIN32

		SOCKET sock;

		#else

		int sock;

		#endif

		public:
		Socket()
		{
			return;
		}
		Socket(SocketTypes t)
		{
			type = t;
		}
		Socket(char *addr, uint16_t port, SocketTypes t)
		{
			type = t;
			sock = socket((type & 0x80 != 0) ? AF_INET6 : AF_INET, type & 0xF, (type & 0xF == 1) ? IPPROTO_TCP : IPPROTO_UDP);
			
			#ifdef __unix__
			
			fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);

			#else

			// TODO: Set non-blocking windows

			#endif

			// TODO: Error handling

			if(type & 0x80 == 0x80)
			if(type & 0x80 == 0x80)
			{
				sockaddr_in6 din;
				addrinfo sug;
				addrinfo *res;
				sug.ai_family = AF_INET6;
				sug.ai_socktype = (type & 0xF == 1) ? IPPROTO_TCP : IPPROTO_UDP;
				sug.ai_protocol = 0;

				getaddrinfo(addr, NULL, &sug, &res); // Works I think

				*(sockaddr*)&din = *res->ai_addr;
				din.sin6_family = AF_INET6;
				din.sin6_port = htons(port);

				freeaddrinfo(res);

				connect(sock, (sockaddr*)&din, sizeof(sockaddr_in6));
			}
			else
			{
				sockaddr_in din;
				addrinfo sug;
				addrinfo *res;
				sug.ai_family = AF_INET;
				sug.ai_socktype = (type & 0xF == 1) ? IPPROTO_TCP : IPPROTO_UDP;
				sug.ai_protocol = 0;

				getaddrinfo(addr, NULL, &sug, &res); // Works I think

				*(sockaddr*)&din = *res->ai_addr;
				din.sin_family = AF_INET;
				din.sin_port = htons(port);

				freeaddrinfo(res);

				connect(sock, (sockaddr*)&din, sizeof(sockaddr_in));
			}
		}
		~Socket()
		{
			close(sock);
		}

		// TODO: Flags
		int write(void *packet, size_t len)
		{
			if(len > 508 && (type & 0xF == 2))
			{
				errorcode() = ENGINE_UNSAFE_UDP_SIZE;
			}
			if(len > 65507 && (type & 0xF == 2))
			{
				errorcode() = ENGINE_TOO_BIG_UDP;
				return -1;
			}

			if(send(sock, packet, len, 0) == -1)
			{
				errorcode() = ENGINE_CLIB_ERRNO_SET;
				return -1;
			}
			
			return 0;
		}

		// TODO: Actual flags
		size_t read(void *buffer, size_t len, bool peek)
		{
			size_t res = recv(sock, buffer, len, (peek) ? MSG_PEEK  : 0 );
			if(res == -1)
			{
				errorcode() = ENGINE_CLIB_ERRNO_SET;
			}

			return res;
		}
	};

#ifdef CITRUS_ENGINE_SERVER_SOCKETS

	class ServerSocket
	{
		SocketTypes type;

		#ifdef _WIN32

		SOCKET sock;

		#else

		int sock;

		#endif

		bool isConnected;

		public:
		typedef void (*JobPointer)(ServerSocket&, void*);
		class ServerJob : public Job
		{
			ServerSocket &sock;
			JobPointer ptr;
			void *arg;
			public:
			void operator()() override
			{
				ServerSocket nuevoSocket;
				nuevoSocket.type = sock.type;
				nuevoSocket.sock = accept(sock.sock, NULL, NULL);
				nuevoSocket.isConnected = true;
				ptr(nuevoSocket, arg);
			}

			bool operator==(ServerJob &otra)
			{
				if(ptr == otra.ptr && sock.sock == sock.sock)
				{
					return true;
				}
				return false;
			}

			bool operator==(Job &otra) override
			{
				if(otra.getTypeSignature() == 0)
				{
					return *this == (ServerJob&)otra;
				}
				return false;
			}

			int getTypeSignature() override
			{
				return 0;
			}
			friend class ServerSocket;
		};

		ServerSocket()
		{
			isConnected = false;
			return;
		}
		ServerSocket(SocketTypes t)
		{
			type = t;
			isConnected = false;
		}
		ServerSocket(char *addr, uint16_t port, SocketTypes t, int listenQueueSize)
		{
			type = t;
			sock = socket((type & 0x80 != 0) ? AF_INET6 : AF_INET, type & 0xF, (type & 0xF == 1) ? IPPROTO_TCP : IPPROTO_UDP);
			isConnected = false;

			// TODO: Error handling

			if(type & 0x80 == 0x80)
			if(type & 0x80 == 0x80)
			{
				sockaddr_in6 din;
				addrinfo sug;
				addrinfo *res;
				sug.ai_family = AF_INET6;
				sug.ai_socktype = (type & 0xF == 1) ? IPPROTO_TCP : IPPROTO_UDP;
				sug.ai_protocol = 0;

				getaddrinfo(addr, NULL, &sug, &res); // Works I think

				*(sockaddr*)&din = *res->ai_addr;
				din.sin6_family = AF_INET6;
				din.sin6_port = htons(port);

				freeaddrinfo(res);

				bind(sock, (sockaddr*)&din, sizeof(sockaddr_in6));
				listen(sock, listenQueueSize);
			}
			else
			{
				sockaddr_in din;
				addrinfo sug;
				addrinfo *res;
				sug.ai_family = AF_INET;
				sug.ai_socktype = (type & 0xF == 1) ? IPPROTO_TCP : IPPROTO_UDP;
				sug.ai_protocol = 0;

				getaddrinfo(addr, NULL, &sug, &res); // Works I think

				*(sockaddr*)&din = *res->ai_addr;
				din.sin_family = AF_INET;
				din.sin_port = htons(port);

				freeaddrinfo(res);

				bind(sock, (sockaddr*)&din, sizeof(sockaddr_in));
				listen(sock, listenQueueSize);
			}
		}
		~ServerSocket()
		{
			close(sock);
		}

		// TODO: Flags
		int write(void *packet, size_t len)
		{
			if(len > 508 && (type & 0xF == 2))
			{
				errorcode() = ENGINE_UNSAFE_UDP_SIZE;
			}
			if(len > 65507 && (type & 0xF == 2))
			{
				errorcode() = ENGINE_TOO_BIG_UDP;
				return -1;
			}

			if(send(sock, packet, len, 0) == -1)
			{
				errorcode() = ENGINE_CLIB_ERRNO_SET;
				return -1;
			}
			
			return 0;
		}

		// TODO: Actual flags
		size_t read(void *buffer, size_t len, bool peek)
		{
			size_t res = recv(sock, buffer, len, (peek) ? MSG_PEEK  : 0 );
			if(res == -1)
			{
				errorcode() = ENGINE_CLIB_ERRNO_SET;
			}

			return res;
		}

		ServerJob handleConnection(JobPointer ptr, void *arg)
		{
			ServerJob j;
			j.ptr = ptr;
			j.sock = *this;
			j.arg = arg;
			return j;
		}
	};
};

#endif

#endif