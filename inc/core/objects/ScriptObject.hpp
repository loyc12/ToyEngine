#ifndef SCRIPTOBJECT_HPP
# define SCRIPTOBJECT_HPP

# include "./BaseObject.hpp"

class ScriptObject : virtual public BaseObject
{
	protected:
	// ================================ ATTRIBUTES
		bool isActive; // whether this object should run its scripts

	// ================================ CORE METHODS
		void onAdd() override;
		void onCpy( const ScriptObject &obj );
		void onDel() override;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		ScriptObject();
		ScriptObject( objID_t id );
		ScriptObject( const ScriptObject &obj );
		ScriptObject &operator=( const ScriptObject &obj );
		~ScriptObject();

	// ================================ ACCESSORS
		bool getIsActive() const;			void setIsActive( bool active );

	// ================================ OPERATORS

	// ================================ METHODS
		void onUpdate(); // ENTRYPOINT : runs the object's scripts
};

#endif // SCRIPTOBJECT_HPP