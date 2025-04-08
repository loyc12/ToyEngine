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

	G_Point = new Object2D;
	G_Point->setShape( Shape2::Point( { 64, -64 }));

	G_Line = new Object2D;
	G_Line->setShape( Shape2::Line( { 256, 128 }, { 16, -8 }));

	G_Square = new Object2D;
	G_Square->setShape( Shape2::Square( { -64, 64 }, { -72, 80 }, 20));
	G_Square->setColor( MAGENTA );

	G_Hexagon = new Object2D;
	G_Hexagon->setShape( Shape2::Hexagon( { -64, 0 }, { 16, 16 }));
	G_Hexagon->setColor( YELLOW );

	G_Polygon = new Object2D;
	G_Polygon->setShape( Shape2::Polygon( { 64, 128 }, { 16, 16 }, 7, 75 ));
	G_Polygon->setColor( GREEN );

	G_Player = new Object2D;
	G_Player->setShape( Shape2::Circle( { 0.0f, 0.0f }, 10.0f ));
	G_Player->setColor( BLUE );

	G_Enemy = new Object2D;
	G_Enemy->setShape( Shape2::Triangle( { 64, 64 }, { 16, 16 }, 40));
	G_Enemy->setColor( RED );

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
