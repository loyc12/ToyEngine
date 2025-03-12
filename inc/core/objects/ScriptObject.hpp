#ifndef SCRIPTOBJECT_HPP
# define SCRIPTOBJECT_HPP

# include "./BaseObject.hpp"

class ScriptObject : public BaseObject
{
	protected:
	// ================================ ATTRIBUTES

	// ================================ CORE METHODS
		void onAdd();
		void onCpy();
		void ondel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		ScriptObject();
		ScriptObject( const ScriptObject &obj );
		ScriptObject &operator=( const ScriptObject &obj );
		~ScriptObject();

	// ================================ ACCESSORS

	// ================================ OPERATORS

	// ================================ METHODS
};

#endif // SCRIPTOBJECT_HPP