#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector.h"
#include <vector>
#include <string>
#include "program.h"

/**
 * @brief The Geometry class
 */
class Geometry
{
public:

    /**
     *	@brief	primitive enums for drawing
     *	parts map to opengl
     */
    typedef enum
    {
        POINTS			= 0x0000,	/**< maps to GL_POINTS. */
        LINES			= 0x0001,	/**< maps to GL_LINES. */
        LINE_LOOP		= 0x0002,	/**< maps to GL_LINE_LOOP. */
        LINE_STRIP      = 0x0003,	/**< maps to GL_LINE_STRIP. */
        TRIANGLES       = 0x0004,	/**< maps to GL_TRIANGLES. */
        TRIANGLE_STRIP  = 0x0005,	/**< maps to GL_TRIANGLE_STRIP. */
        TRIANGLE_FAN    = 0x0006,	/**< maps to GL_TRIANGLE_FAN. */

        QUADS,						/**< compatibility for quads. we are triangulating them. */
        QUAD_STRIP					/**< compatibility for quad strips. we are triangulating them. */
    }
    primitive;

    /**
     * @brief Geometry
     */
    Geometry();

    /**
     * @brief Geometry
     * @param m_FilePath the path to the obj file to load
     */
    Geometry(std::string m_FilePath);

    /**
     * @brief ~Geometry
     */
    virtual ~Geometry();

    /**
     *  @brief draw
     *  draws the geometry to the screen
     *  @param  m_Program the shader program to be used for drawing
     */
    void draw(Program * m_Program = NULL);
	
	/**
	 *	translates each vertex by the given translation
	 *	@param	m_Translation the translation vector
	 */
	void translate(Vector3 m_Translation);

    /**
     * @brief scale
     * @param m_ScaleFactor the new scale factor
     */
    void scale(float m_ScaleFactor);

    /**
     * @brief getFileName
     * @return returns the file name of our geometry
     */
    std::string getFileName() const;

    /**
     * @brief getFilePath
     * @return returns the full path of our geometry
     */
    std::string getFilePath() const;

private:

    /**
     *  @brief parseFile
     *  method that parses the obj file
     */
    void parseFile();
	
	/**
	 *	converts the model stored as quads into triangles
	 */
	void convertQuadsToTriangles();
	
	/**
	 *	initialises the OpenGL buffers we need for drawing
	 */
	void initOpenGLBuffers();
	
	/**	
	 *	initializes the default shader
	 *	@return	returns if success
	 */
	bool initDefaultShader();

     std::string    mFileName;              /**< the file name of the model if set. */
     std::string    mFilePath;              /**< the full cannonical path to the model file, if set. */

    unsigned int mColorBuffer;				/**< handle for the color buffer. */
    unsigned int mNormalBuffer;				/**< handle for the normal buffer. */
    unsigned int mTexCoordBuffer;			/**< handle for the texture coordinate buffer. */
    unsigned int mVertexBuffer;				/**< handle for the vertex buffer. */

    unsigned int mVertexArray;				/**< the VAO handle. */

    primitive				mPrimitiveType;		/**< the drawing primitivetype. */

    std::vector<Vector3>	mVertices;		/**< the array for the vertices. */
    std::vector<Vector3>	mNormals;		/**< the array for the normals. */
    std::vector<Vector3>	mTexCoords;		/**< the array for the texture coordinates.
											 *	2d texture coordinates are expanded to have 0 in z. */
    std::vector<Vector4>	mColors;		/**< the array for the colors.
                                                 *	The w is added with 1, when not present. */
    Program    * mProgram;          /**< the shader program we use to render our geometry. */

    float       mScaleFactor;           /**< the current scalefactor of the geometry. */
};


#endif // GEOMETRY_H
