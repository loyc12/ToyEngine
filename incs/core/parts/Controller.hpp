#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

# include <raylib.h>
# include "../../base.hpp"
# include "../objects/BaseObject.hpp"


struct inputs_s
{
	// BASE
	bool LEFT,  RIGHT, FORE, BACK;
	bool SPACE, ENTER, SHIFT;
	bool CTRL,  ALT,   TAB;

	// MOUSE
	bool CLICK_LEFT, CLICK_MID, CLICK_RIGHT;
	bool SCROLL_UP,  SCROLL_DOWN;

	// LETTERS
	bool A, B, C, D, E, F, G, H, I, J, K, L, M;
	bool N, O, P, Q, R, S, T, U, V, W, X, Y, Z;

	// DIGITS
	bool D0, D1, D2, D3, D4, D5, D6, D7, D8, D9;
	bool K0, K1, K2, K3, K4, K5, K6, K7, K8, K9;
};

class Controller
{
	private:
	// ================================ ATTRIBUTES
		inputs_s _latestInputs;
		inputs_s _previousInputs;

		// ================================ CORE METHODS
		void init();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Controller();
		~Controller();

	// ================================ ACCESSORS
		inputs_s &getLatestInputs();
		inputs_s &getPreviousInputs();

	// ================================ OPERATORS

	// ================================ METHODS
		void refreshInputs();


};


#endif // CONTROLLER_HPP