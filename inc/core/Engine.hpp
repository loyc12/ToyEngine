#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "./objects/Object2D.hpp"
# include "./display/Viewport.hpp"
#include <cstdint>

typedef enum : byte_t
{
	E_UNINITIALIZED = 0,
	E_INITIALIZED,
	E_RUNNING

} engineState_e;

class Engine // make this a static class ???
{
	private:
	// ================================ ATTRIBUTES
		// gobal var struct
		// viewport/canvas
		vector< BaseObject* > ObjectContainer;
		engineState_e state;
		objID_t maxID;

	// ================================ CONSTRUCTORS / DESTRUCTORS

	// prevents the singleton from being copied
		Engine( const Engine &cpy ) = delete;
		Engine &operator=( const Engine &cpy ) = delete;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Engine();
		~Engine();

		static Engine *getEngine();

	// ================================ CORE METHODS
		void start();
		void close();
		void launch(); // calls the method below in a loop
		void runStep(); // calls the 4 methods below in order

		void readInputs(); // reads the inputs, updates the global var struct & calls the onInput() method of every object
		void runPhysics(); // calls the onTick() method of every object
		void runScripts(); // calls the onUpdate() method of every object
		void renderObjects(); // calls the onRefresh() method of every object

	// ================================ OBJECTS METHODS

		BaseObject *addObject( BaseObject *ob, bool checkForDupID = false ); // NOTE : put to true by default ?
		bool delObject( BaseObject *obj );
		bool delObjectByID( objID_t id );
		void DelAllObjects();

	// ================================ ACCESSORS
		BaseObject *getObjectByID( objID_t id );

		objID_t getNewID();
		objID_t getState() const;
		uint32_t getObjectCount() const;



	// ================================ OPERATORS

	// ================================ METHODS

};

#endif // ENGINE_HPP