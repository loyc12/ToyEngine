#include "../incs/base.hpp"
#include "../incs/core.hpp"
#include "../incs/game.hpp"

void test_CompManager()
{
	flog( 0 );

	GCM->addEntity( 1 );
	GCM->addThatEntity( new GameEntity() );

	GameEntity ent = GCM->getEntity( 1 );
	ent.addThatComponent( new CompPos() );

	ent = GCM->getEntity( 2 );
	ent.addComponent< CompPos >();
	qlog( "Entity ID: " + std::to_string( ent.getID()), INFO, 0 );

	ent = GCM->getEntity( 1 );
	CompPos pos = ent.getComponent< CompPos >();
	qlog( "Entity ID: "     + std::to_string( ent.getID()), INFO, 0 );
	qlog( "Component ID: "  + std::to_string( pos.getID()), INFO, 0 );
	qlog( "Component Pos: " + std::to_string( pos.getPos().x ) + ", " + std::to_string( pos.getPos().y ), INFO, 0 );
	ent.delComponent< CompPos >();
	ent.addThatComponent( new CompPos( true, 1, { 2, 2 } ) );

	pos = ent.getComponent< CompPos >();
	qlog( "Component ID: "  + std::to_string( pos.getID()), INFO, 0 );
	qlog( "Component Pos: " + std::to_string( pos.getPos().x ) + ", " + std::to_string( pos.getPos().y ), INFO, 0 );

	ent.delEntity();
	ent = GCM->getEntity( 1 );

	GCM->delEntity( 2 );
	ent = GCM->getEntity( 2 );
}

int main()
{
	flog( 0 );

	//GNG->switchState( ES_STARTED );
	//test_CompManager();

	GNG->switchState( ES_RUNNING );

	GNG->launchLoop();

	GNG->switchState( ES_CLOSED );

	delete GNG;   GNG = nullptr;

	qlog( "Exiting main()", INFO, 0 );
}