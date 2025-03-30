#ifndef SCRIPTOBJECT_HPP
# define SCRIPTOBJECT_HPP

# include "./BaseObject.hpp"

class ScriptObject : virtual public BaseObject
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
		~ScriptObject();

	// ================================ ACCESSORS
		bool getIsActive() const;			void setIsActive( bool _isActive );

	// ================================ OPERATORS

	// ================================ METHODS
		void onScriptTick() override; // ENTRYPOINT : runs the object's scripts
		// TODO : used a customizable function pointer array to add/remove scripts to an object
};

#endif // SCRIPTOBJECT_HPP