#ifndef SCRIPTOBJECT_HPP
# define SCRIPTOBJECT_HPP

# include <raylib.h>
# include "./PhysicObject.hpp"

class ScriptObject :
	virtual public BaseObject,
	virtual public ShapeObject,
	virtual public RenderObject,
	virtual public PhysicObject
{
	// this class is used to run scripts from an object
	protected:
	// ================================ ATTRIBUTES
		bool _isActive; // whether this object should run its scripts

	// ================================ CORE METHODS
		void onAdd() override;
		void onCpy(  const ScriptObject &obj );
		void onDel() override;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		ScriptObject();
		ScriptObject( const ScriptObject &obj );
		ScriptObject &operator=( const ScriptObject &obj );
		virtual ~ScriptObject();

	// ================================ ACCESSORS / MUTATORS
		bool getIsActive() const;			void setIsActive( bool _isActive );

	// ================================ TICK METHODS
		void onScriptTick() override; // ENTRYPOINT : (re)runs the object's scripts

		// TODO : used a customizable function pointer array to add/remove scripts to an object
};

#endif // SCRIPTOBJECT_HPP