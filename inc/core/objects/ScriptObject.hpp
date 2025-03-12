#ifndef SCRIPTOBJECT_HPP
# define SCRIPTOBJECT_HPP

# include "./BaseObject.hpp"

class ScriptObject : public BaseObject
{
	protected:
	// ================================ ATTRIBUTES
		bool isActive; // whether this object should run its scripts

	// ================================ CORE METHODS
		void onUpdate(); // ENTRYPOINT : runs the object's scripts

		virtual void onAdd();
		virtual void onCpy( const ScriptObject &obj );
		virtual void onDel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		ScriptObject();
		ScriptObject( const ScriptObject &obj );
		ScriptObject &operator=( const ScriptObject &obj );
		~ScriptObject();

	// ================================ ACCESSORS
		bool getIsActive() const;			void setIsActive( bool active );

	// ================================ OPERATORS

	// ================================ METHODS
};

#endif // SCRIPTOBJECT_HPP