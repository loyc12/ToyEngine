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
	G_Point->setShape( Shape2::Point({ 0, 0 }));
	G_Point->setColor( WHITE );

	G_Line = new Object2D;
	G_Line->setShape(      Shape2::Line(     { 64, 128 },    { -64, -128 }));
	G_Line->setColor(      PINK );

	G_Triangle = new Object2D;
	G_Triangle->setShape(  Shape2::Triangle( { 128, 128 },   { 128, 144 }));
	G_Triangle->setColor(  RED );

	G_Diamond = new Object2D;
	G_Diamond->setShape(   Shape2::Diamond(  { 128, 0 },     { 16, 24 }, 10));
	G_Diamond->setColor(   ORANGE );

	G_Square = new Object2D;
	G_Square->setShape(    Shape2::Square(   { 128, -128 },  { 128, -144 }, 20));
	G_Square->setColor(    YELLOW );

	G_Rectangle = new Object2D;
	G_Rectangle->setShape( Shape2::Rectangle({ 0, -128 },    { 32, 16 }, 30));
	G_Rectangle->setColor( LIME );

	G_Circle = new Object2D;
	G_Circle->setShape(    Shape2::Circle(   { -128, -128 }, { -144, -128 }));
	G_Circle->setColor(    GREEN );

	G_Ellipse = new Object2D;
	G_Ellipse->setShape(   Shape2::Ellipse(  { -128, 0 },    { 16, 32 }, 30));
	G_Ellipse->setColor(   SKYBLUE );

	G_Pentagon = new Object2D;
	G_Pentagon->setShape(  Shape2::Pentagon( { -128, 128 },  { 16, 16 }, 40 ));
	G_Pentagon->setColor(  BLUE );

	G_Hexagon = new Object2D;
	G_Hexagon->setShape(   Shape2::Hexagon(  { 0, 128 },     { 16, 16 }, 50 ));
	G_Hexagon->setColor(   DARKBLUE  );

	G_Octogon = new Object2D;
	G_Octogon->setShape(   Shape2::Octogon(  { 256, 0 },     { 16, 16 }, 60 ));
	G_Octogon->setColor(   PURPLE );

	G_Dodecagon = new Object2D;
	G_Dodecagon->setShape( Shape2::Dodecagon({ -256, 0 },    { 16, 16 }, 70 ));
	G_Dodecagon->setColor( VIOLET );

	G_Polygon = new Object2D;
	G_Polygon->setShape(   Shape2::Polygon(  { 0, 256 },     { 16, 16 }, 7, 80 ));
	//G_Polygon->setShape(   Shape2::Polygon({{ 16, 16 }, { 16, -32 }, { -16, -8 }, { -16, 24 }})); // TODO : debug my rendering
	G_Polygon->setColor(   MAGENTA );


	G_Player = new Object2D;
	G_Player->setShape( Shape2::Circle( { 0, 0 }, 12 ));
	G_Player->setColor( GOLD );

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
