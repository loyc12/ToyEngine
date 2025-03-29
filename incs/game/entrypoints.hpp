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
void OnRenderUI();

void OnEach( PhysicObject *obj );
void OnEach( ScriptObject *obj );
void OnEach( RenderObject *obj );

#endif // ENTRYPOINT_HPP