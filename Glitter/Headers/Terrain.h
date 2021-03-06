//
// Created by Dradozer on 17.05.2020.
//

#ifndef GLITTER_TERRAIN_H
#define GLITTER_TERRAIN_H

// headers
#include <imgui.h>
#include "../Sources/GUI/include/baseObject.h"
#include "../Sources/GUI/include/sceneInfo.h"
#include "../Sources/GUI/include/Window.h"
#include <iostream>
#include <vector>
#include <map>

#include "ezr_shader.h"
#include "../Sources/EZR_Shader/ezr_ssbo.h"
#include "ezr_computeShader.h"

#include "cmpVecs.h"
#include "Chunk.h"
#include "Texture.h"


class Terrain : public baseObject
{
public:
    /**
     * Constructor of Terrain
     * @param camera
     * @param seed
     */

    virtual void setGui();
    virtual void draw();
    virtual void update();

    Terrain(Window *window, sceneInfo *scene, const int seed = 42069, int dimensions = 20);

    virtual ~Terrain();

    void render();

    Camera *getCamera() const;
    unsigned int sandTex, grassTex, snowTex, grass1Tex, rockTex, normalTex;


private:
    /**
     * is implemented in C++20, this is just a slow alternative
     */
    bool contains(glm::ivec2);

    /**
     * passes glUniforms to Shader
     * @param id ShaderID
     */
    void setUniforms(GLuint &id);

    /**
     * @param how many Chunk are generated around the Player
     */
    int m_chunkDimensions;
    void set2dTex( GLuint location , unsigned int texture , int id ) const;

    Window *m_window;
    sceneInfo *m_scene;
    const int m_seed;
    // m_patchSize: number of Vertices, m_chunkSizeMult: multiplicator for Vertice.Position, m_chunkSize: size of Chunk in 3D-Coord-Unit
    const int m_patchSize, m_chunkSizeMult;
    int m_chunkSize;
    glm::vec4 m_LoD = glm::vec4(20,10,5,3);
    bool m_tesse = false;

    std::map<glm::ivec2, Chunk, cmpVecs> m_chunkDictionary;

    GLuint m_renderTerrainID;
    GLuint m_uniform_camPos;
    GLuint m_uniform_viewM;
    GLuint m_uniform_projM;
    //tesselationstuffadressen, kann im array gefasst werden
    GLuint m_lightPos;
    GLuint m_eyePos;
    GLuint m_displaceFactor;
    GLuint m_chunkPos;
    GLuint m_useed;
    GLuint m_lod_b;
    GLuint m_lod_v4;
    Texture *nTexture;
    volatile GLuint m_uniform_SandTextureLoc;
    volatile GLuint m_uniform_GrassTextureLoc;
    volatile GLuint m_uniform_SnowTextureLoc;
    volatile GLuint m_uniform_Grass1TextureLoc;
    volatile GLuint m_uniform_RockTextureLoc;
    volatile GLuint m_uniform_rockNormalTextureLoc;


};

#endif //GLITTER_TERRAIN_H
