#ifndef INJECTORS_HPP
# define INJECTORS_HPP

# include "../core.hpp"

/*
these functions are called by the engine at the end of there respective function calls
they are used to inject game specific code into the engine without modifying the engine itself
*/

// ==================== ENGINE CORE INJECTION FUNCTIONS
// for when the engine changes state
	void OnGameInit();
		void OnGameStart();
			void OnGameResume();

			void OnGamePause();
		void OnGameStop();
	void OnGameClose();

// ==================== ENGINE STEP INJECTION FUNCTIONS
// for when the engine calls the game step method
	void OnGameLaunch();
		void OnGameStep();
			void OnReadInputs();
			void OnRunPhysics();
			void OnRunScripts();
			void OnRenderWorld();
			void OnRenderUI();

// ===================== OBJECT STEP INJECTION FUNCTIONS
// for when the engine calls the object update methods
	void OnPhysicCall( PhysicObject *obj ); // only called when the game is unpaused
	void OnScriptCall( ScriptObject *obj );
	void OnRenderCall( RenderObject *obj );

#endif // INJECTORS_HPP