#ifndef ENTRYPOINT_HPP
# define ENTRYPOINT_HPP

# include "../core.hpp"

void OnGameStart();
void OnGameStep();
void OnGameClose();

void OnReadInputs();
void OnRunPhysics();
void OnRunScripts();
void OnRenderObjects();

#endif // ENTRYPOINT_HPP