#ifndef ENGINE_H
#define ENGINE_H
// hylee
#define HYLEE
#define DEBUG_HY
#define NO_CACHE

#include <iostream>
#include <unordered_map>
#include "Sim_Defs.h"
#include "EventTree.h"
#include "Sim_Object.h"



namespace MQSimEngine {
	class Engine
	{
		friend class EventTree;
	public:
		Engine()
		{
			this->_EventList = new EventTree;
			started = false;
		}

		~Engine() {
			delete _EventList;
		}
		
		static Engine* Instance();
		sim_time_type Time();
		Sim_Event* Register_sim_event(sim_time_type fireTime, Sim_Object* targetObject, void* parameters = NULL, int type = 0);
		void Ignore_sim_event(Sim_Event*);
		void Reset();
		void AddObject(Sim_Object* obj);
		Sim_Object* GetObject(sim_object_id_type object_id);
		void RemoveObject(Sim_Object* obj);
		void Start_simulation();
		void Stop_simulation();
		bool Has_started();
		bool Is_integrated_execution_mode();
		sim_time_type sim_time_before_PRECOND;
		sim_time_type sim_time_before_GC;
	private:
		sim_time_type _sim_time;
		EventTree* _EventList;
		std::unordered_map<sim_object_id_type, Sim_Object*> _ObjectList;
		bool stop;
		bool started;
		static Engine* _instance;
	};
}

#define Simulator MQSimEngine::Engine::Instance()
#endif // !ENGINE_H
