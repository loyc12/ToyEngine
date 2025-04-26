#include "../incs/base.hpp"
#include "../incs/core.hpp"
#include "../incs/game.hpp"

void test_CompManager()
{
	flog( 0 );

	GCM->addEntity( 0 );
	GCM->addEntity( 1 );
	GCM->addThatEntity( new GameEntity( false, 2 ));
	new GameEntity();
	GCM->addEntity( 7 );
	new GameEntity();
	new GameEntity( true, 5 );

	qlog( "Listing entities", INFO, 0 );
	GameEntity* ge;
	for ( int i = 0; i < 10; ++i )
	{
		ge = GCM->getEntity( i );
		if ( ge ){ qlog( "Entity ID : " + std::to_string( ge->getID() ), INFO, 0 ); }
		else{ qlog( "No entity found with ID: " + std::to_string( i ), INFO, 0 ); }
	}

	qlog( "Adding components to entities", INFO, 0 );

	GCM->getEntity( 1 )->addComponent< CompPos >();
	GCM->getEntity( 2 )->addThatComponent( new CompPos() );
	GCM->getEntity( 3 )->addThatComponent( new CompPos( true ));
	GCM->addComponent< CompPos >( 5 );
	GCM->getEntity( 7 )->addThatComponent( new CompPos( true, 8, { 1, 2 } ));
	GCM->addThatComponent( 8, new CompPos( true, 8, { 657, 4356 } ));

	qlog( "listing components", INFO, 0 );
	for( int i = 0; i < 10; ++i )
	{
		ge = GCM->getEntity( i );
		if ( ge )
		{
			qlog( "Entity ID : " + std::to_string( ge->getID() ), INFO, 0 );

			CompPos* cp = GCM->getComponent< CompPos >( i );

			if ( cp )
			{
				qlog( "Component ID : " + std::to_string( cp->getID() ), INFO, 0 );
				qlog( "Component Pos : " + std::to_string( cp->getPos().x ) + ", " + std::to_string( cp->getPos().y ), INFO, 0 );
			}
			else{ qlog( "No component found with ID: " + std::to_string( i ), INFO, 0 ); }

		}
		else{ qlog( "No entity found with ID: " + std::to_string( i ), INFO, 0 ); }

	}
}

int main()
{
	flog( 0 );

	GNG->switchState( ES_STARTED );
	test_CompManager();

	//GNG->switchState( ES_RUNNING );
	//GNG->launchLoop();

	GNG->switchState( ES_CLOSED );

	delete GNG;   GNG = nullptr;

	qlog( "Exiting main()", INFO, 0 );
}