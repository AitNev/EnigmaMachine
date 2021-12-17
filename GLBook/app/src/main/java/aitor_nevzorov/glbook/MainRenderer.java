package aitor_nevzorov.glbook;

import android.content.Context;
import android.opengl.GLSurfaceView;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import aitor_nevzorov.glbook.utils.LoggerConfig;
import aitor_nevzorov.glbook.utils.ShaderHelper;
import aitor_nevzorov.glbook.utils.TextResourceReader;

import static android.opengl.GLES20.*;
import static android.opengl.GLUtils.*;
import static android.opengl.Matrix.*;

public class MainRenderer implements GLSurfaceView.Renderer {
    private static final int POSITION_COMPONENT_COUNT = 2;
    private static final int BYTES_PER_FLOAT = 4;

    private static final String U_COLOR = "u_Color";
    private static final String U_Matrix = "u_Matrix";
    private static final String A_Position = "a_Position";

    private final float[] projectionMatrix = new float[16];
    private final FloatBuffer vertexData;
    private final Context context;

    private int uColorLocation;
    private int uMatrixLocation;
    private int aPositionLocation;

    private int program;

    public MainRenderer(Context context){
        this.context = context;
        float[] vertices = {
                0f, 0f,
                0f, 14f,
                9f, 14f,
                9f, 0f
        };
        float[] tableVerticesWithTriangles = {
                // Triangle 1
                -0.5f, -0.8f,
                0.5f, -0.8f,

                // Triangle 2
                0.5f, 0.8f,
                -0.5f, 0.8f,

                // Line 1
                -0.5f, 0f,
                0.5f, 0f,

                //Mallets
                0f, -0.4f,
                0f, 0.4f
        };

        vertexData = ByteBuffer.allocateDirect(tableVerticesWithTriangles.length*BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        vertexData.put(tableVerticesWithTriangles);
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        String vertexShaderSource = TextResourceReader
                .readTextFileFromResource(context, R.raw.simple_vertex_shader);
        String fragmentShaderSource = TextResourceReader
                .readTextFileFromResource(context, R.raw.simple_fragment_shader);
        int vertexShader = ShaderHelper.compileVertexShader(vertexShaderSource);
        int fragmentShader = ShaderHelper.compileFragmentShader(fragmentShaderSource);
        this.program = ShaderHelper.linkProgram(vertexShader, fragmentShader);
        if (LoggerConfig.ON){
            ShaderHelper.validateProgram(program);
        }

        glUseProgram(program);
        uColorLocation = glGetUniformLocation(program, U_COLOR);
        uMatrixLocation = glGetUniformLocation(program, U_Matrix);

        aPositionLocation = glGetAttribLocation(program, A_Position);
        vertexData.position(0);
        glVertexAttribPointer(aPositionLocation, POSITION_COMPONENT_COUNT,
                GL_FLOAT, false, 0, vertexData);
        glEnableVertexAttribArray(aPositionLocation);
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        glViewport(0,0,width,height);
        final float aspectRatio = width > height ? (float) width /
                (float) height : (float) height / (float) width;
        if(width > height){
            // Landscape
            orthoM(projectionMatrix, 0, -aspectRatio, aspectRatio, -1f, 1f, -1f, 1f);
        }else{
            orthoM(projectionMatrix,0, -1f, 1f, -aspectRatio, aspectRatio, -1f, 1f);
        }
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        glClear(GL_COLOR_BUFFER_BIT);

        //uploading matrix
        glUniformMatrix4fv(uMatrixLocation, 1, false, projectionMatrix, 0);
        // Triangles
        glUniform4f(uColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // Line
        glUniform4f(uColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_LINES, 4, 2);
        // Blue Mallet
        glUniform4f(uColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
        glDrawArrays(GL_POINTS, 6, 1);
        // Red Mallet
        glUniform4f(uColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_POINTS, 7, 1);
    }

    public void handleTouchPress(float XCoord, float YCoord){
        // 8,9
        float[] tableVerticesWithTriangles = {
                // Triangle 1
                -0.5f, -0.8f,
                0.5f, -0.8f,

                // Triangle 2
                0.5f, 0.8f,
                -0.5f, 0.8f,

                // Line 1
                XCoord,YCoord,
                0.5f, 0f,

                //Mallets
                0f, -0.4f,
                0f, 0.4f
        };
    }
    public void handleTouchDrag(float XCoord, float YCoord){
        // 10, 11
        float[] tableVerticesWithTriangles = {
                // Triangle 1
                -0.5f, -0.8f,
                0.5f, -0.8f,

                // Triangle 2
                0.5f, 0.8f,
                -0.5f, 0.8f,

                // Line 1
                -0.5f, 0f,
                XCoord, YCoord,

                //Mallets
                0f, -0.4f,
                0f, 0.4f
        };
    }
    private void changeLine(boolean isEnd, int XCoord, int YCoord){
        float[] tableVerticesWithTriangles = {
                // Triangle 1
                -0.5f, -0.8f,
                0.5f, -0.8f,

                // Triangle 2
                0.5f, 0.8f,
                -0.5f, 0.8f,

                // Line 1
                -0.5f, 0f,
                0.5f, 0f,

                //Mallets
                0f, -0.4f,
                0f, 0.4f
        };if(isEnd){
            tableVerticesWithTriangles[10] = XCoord;
            tableVerticesWithTriangles[11] = YCoord;
        }else{
            tableVerticesWithTriangles[8] = XCoord;
            tableVerticesWithTriangles[9] = YCoord;
        }
    }
}
