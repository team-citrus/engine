/*
*   name: include/physics/physmain.hpp
*   origin: Citrus Engine
*   purpose: Provides the main function for physics
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PHYSICS_MAIN_HPP__
#define CITRUS_ENGINE_PHYSICS_MAIN_HPP__

#include <box2d/box2d.h>
#include <btBulletDynamicsCommon.h>
#include "../core/vector.hpp"
#define _INTERNALS_ENGINE_THREAD_MAIN_
#include "../core/jobsys.hpp"
#include "../core/object.hpp"
#include "../physics/collider.hpp"

#define INTERNALS_PHYSICS_DEQUEUE_ERR_NOT_FOUND -1
#define INTERNALS_PHYSICS_QUEUE_ERR_ALREADY_QUEUED -1

namespace engine
{
namespace internals
{
	namespace physics
	{
		// Initalize physics
		void Init(bool 2D, Vec3 gravity);

		// Deconstruct physics
		void Fini();

		/*  Steps the main physics simulation
		*   @warning THIS SHOULD ONLY BE CALLED WITHIN physmain()
		*   DO NOT CALL IT ANYWHERE ELSE UNLESS YOU WANT TO SERIOUSLY MESS THINGS UP.
		*   @return Any error codes that might arrise
		*/
		int step();

		/*	Updates all of the phyics objects after step
		*   @warning THIS SHOULD ONLY BE CALLED WITHIN physmain()
		*   DO NOT CALL IT ANYWHERE ELSE UNLESS YOU WANT TO SERIOUSLY MESS THINGS UP.
		*	return Any error codes that might arrise 
		*/
		int updateObjects();

		class b2Listener : public b2ContactListener
		{
			public:
			class ContactJob : Job
			{
				public:
				b2Contact *ptr;
				bool enterOrExit;
				int getTypeSignature() override
				{
					return 0xb2C2D;
				}

				bool operator==(Job &otra) override
				{
					if(job.getTypeSignature() == getTypeSignature())
					{
						return *this == *(ContactJob*)&otra;
					}
				}
				bool operator==(ContactJob &otra)
				{
					if(otra.ptr == ptr)
						return true;
				}
				hash_t hash() override
				{
					return engine::hash(this, sizeof(*this));
				}
				void operator()() override
				{
					if(ptr->GetFixtureA()->IsSensor())
					{
						Collider2DTouple *a = (Collider2DTouple*)(ptr->GetFixtureA()->GetUserData().pointer);
						Collider2DTouple *b = (Collider2DTouple*)(ptr->GetFixtureB()->GetUserData().pointer);
						Vector<Component*> v = a->o->getComponents();

						for(int i = 0; i < v.getCount(); i++)
						{
							if(enterOrExit)
							{
								v[i]->onTriggerEnter2D(b->c);
							}
							else // TODO: onTriggerStay
							{
								v[i]->onTriggerExit2D(b->c);
							}
						}
					}
					if(ptr->GetFixtureB()->IsSensor())
					{
						Collider2DTouple *a = (Collider2DTouple*)(ptr->GetFixtureA()->GetUserData().pointer);
						Collider2DTouple *b = (Collider2DTouple*)(ptr->GetFixtureB()->GetUserData().pointer);
						Vector<Component*> v = b->o->getComponents();

						for(int i = 0; i < v.getCount(); i++)
						{
							if(enterOrExit)
							{
								v[i]->onTriggerEnter2D(a->c);
							}
							else // TODO: onTriggerStay
							{
								v[i]->onTriggerExit2D(a->c);
							}
						}
					}
				}
			}

			void BeginContact(b2Contact *thingy) override;
			void EndContact(b2Contact *thingy) override;
		}

		// State of physics
		class PHYS_STATE
		{
			public:
			bool is2D;
			int stepRate;
			union
			{
				Vec2 gravity2D;
				Vec3 gravity3D;
			};
			
			union
			{
				b2World *world2D;
				btDiscreteDynamicsWorld *world3D;
			};
		}

		extern b2Listener listener;

		// The physics state
		extern PHYS_STATE state;
	};
};
};
#endif