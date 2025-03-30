# include <raylib.h>
# include "../../incs/game.hpp"

// ==================== ENGINE CORE INJECTION FUNCTIONS
// called when the engine changes state

void OnGameInit()
// NOTE : do not instanciate objects here ( or do anything that requires the engine to be started )
{
	log( "OnGameInit()", INFO );
}
void OnGameStart()
{
	log( "OnGameStart()", INFO );

	// NOTE : this is a temporary solution, the engine should be able to load the game from a file

	Floor	 = new Object2D;
	Wall1	 = new Object2D;
	Wall2	 = new Object2D;
	Ball   = new Object2D;
	Box    = new Object2D;
	Player = new Object2D;
	Enemy  = new Object2D;

	Floor->setShape(  SHAPE_RECT );
	Floor->setColor(  BLUE );

	Wall1->setShape(  SHAPE_RECT );
	Wall1->setColor(  PINK );

	Wall2->setShape(  SHAPE_RECT );
	Wall2->setColor(  ORANGE );

	Player->setShape( SHAPE_CIRCLE );
	Player->setColor( GREEN );

	Enemy->setShape(  SHAPE_CIRCLE );
	Enemy->setColor(  RED );

	Ball->setShape(   SHAPE_CIRCLE );
	Ball->setColor(   YELLOW );

	Box->setShape(    SHAPE_RECT );
	Box->setColor(    DARKGRAY );

	Floor->setPosition( { 0, -64 });
	Floor->setSize( { 512, 16 });

	Wall1->setPosition( { 64, -32 });
	Wall1->setSize( { 8, 32 });

	Wall2->setPosition( { -128, -32 });
	Wall2->setSize( { 8, 32 });

	Ball->setPosition( { 0, 128 });
	Ball->setSize( { 32, 32 });

	Box->setPosition( { 0, 64 });
	Box->setSize( { 32, 32 });

	Player->setPosition( { 0, 0 });
	Player->setSize( { 16, 16 });

	Enemy->setPosition( { 0, 256 });
	Enemy->setSize( { 16, 16 });

	log( "Created " + std::to_string( GNG->getObjectCount() ) + " objects", INFO );
}
void OnGameResume()
{
	log( "OnGameResume()", INFO );
}

void OnGamePause()
{
	log( "OnGamePause()", INFO );
}
void OnGameStop()
{
	log( "OnGameStop()", INFO );
}
void OnGameClose() // The engine takes care to delete all objects
{
	log( "OnGameClose()", INFO );
}
