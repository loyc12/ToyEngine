#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "../base.hpp"
# include "./objects/Object2D.hpp"
# include "./display/Viewport.hpp"


typedef enum : byte_t
{
	E_UNINITIALIZED = 0,
	E_INITIALIZED,
	E_STARTED,
	E_RUNNING

} engineState_e;

struct inputs_s
{
	//BASE
	bool LEFT;
	bool RIGHT;
	bool FORE;
	bool BACK;
	bool SPACE;
	bool ENTER;
	bool SHIFT;
	bool CTRL;
	bool ALT;
	bool TAB;

	//MOUSE
	bool CLICK_LEFT;
	bool CLICK_MID;
	bool CLICK_RIGHT;
	bool SCROLL_UP;
	bool SCROLL_DOWN;

	//KEYBOARD
	bool Q;
	bool E;
	bool R;
	bool F;
	bool Z;
	bool X;
	bool C;
	bool V;
};

class Engine
{
	private:
	// ================================ CORE METHODS
		void init(); // initializes the engine's data
		void runStep(); // calls the 4 object update methods

		void readInputs(); // reads the inputs, updates the global var struct & calls the onInput() method of every object
		void runPhysics(); // calls the onTick() method of every object
		void runScripts(); // calls the onUpdate() method of every object
		void renderObjects(); // calls the onRefresh() method of every object

	// ================================ ATTRIBUTES
		// gobal var struct
		Viewport2D *_viewport;
		vector< BaseObject* > ObjectContainer;
		inputs_s _lastestInputs;
		inputs_s _previousInputs;
		engineState_e _state;
		objID_t maxID;

	// ================================ CONSTRUCTORS / DESTRUCTORS
	// prevents this singleton from being copied
		Engine( const Engine &cpy ) = delete;
		Engine &operator=( const Engine &cpy ) = delete;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Engine();
		~Engine();

		static Engine *getEngine();

	// ================================ CORE METHODS
		void start(); //  opens the window and redies the engine for the game loop
		void launch(); // calls the 4 object update methods in a loop
		void close(); //  closes the window and frees the memory

	// ================================ OBJECTS METHODS
		BaseObject *addObject( BaseObject *ob, bool checkForDupID = false ); // NOTE : put to true by default ?
		bool delObject( BaseObject *obj );
		bool delObjectByID( objID_t id );
		void DelAllObjects();

	// ================================ ACCESSORS
		inputs_s   &getLastestInputs();
		inputs_s   &getPreviousInputs();

		Viewport2D   *getViewport();
		BaseObject *getObjectByID( objID_t id );

		objID_t getNewID();
		objID_t getState() const;
		uint32_t getObjectCount() const;

	// ================================ OPERATORS

	// ================================ METHODS

};

#endif // ENGINE_HPP