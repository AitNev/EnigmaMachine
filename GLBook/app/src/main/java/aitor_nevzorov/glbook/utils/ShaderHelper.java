package aitor_nevzorov.glbook.utils;

import android.util.Log;

import static android.opengl.GLES20.*;

public class ShaderHelper {
    private static final String TAG = "ShaderHelper";

    public static int compileVertexShader(String shaderCode){
        return compileShader(GL_VERTEX_SHADER, shaderCode);
    }

    public static int compileFragmentShader(String shaderCode){
        return compileShader(GL_FRAGMENT_SHADER, shaderCode);
    }

    private static int compileShader(int type, String shaderCode){
        final int shaderObjectId = glCreateShader(type);

        if(shaderObjectId == 0){
            if(LoggerConfig.ON){
                Log.w(TAG, "Couldnt create new shader");
            }
            return 0;
        }
        glShaderSource(shaderObjectId, shaderCode);
        glCompileShader(shaderObjectId);

        final int[] compileStatus = new int[1];
        glGetShaderiv(shaderObjectId, GL_COMPILE_STATUS, compileStatus, 0);
        if(LoggerConfig.ON){
            // Print info log out
            Log.v(TAG, "Results of compiling source:"+"\n"+shaderCode+"\n:"+glGetShaderInfoLog(shaderObjectId));
        }

        if(compileStatus[0] == 0){
            // If it failed delete the shader obj
            glDeleteShader(shaderObjectId);

            if (LoggerConfig.ON){
                String shaderType;
                if (type == GL_VERTEX_SHADER){
                    shaderType = "vertex";
                }else{
                    shaderType = "fragent";
                }
                Log.w(TAG, "Compilation "+shaderType+"shader failed");
            }
            return 0;
        }
        return shaderObjectId;
    }
    public static int linkProgram(int vertexShaderID, int fragmentShaderID){
        final int programObjectID = glCreateProgram();
        if(programObjectID == 0){
            if (LoggerConfig.ON){
                Log.w(TAG, "Couldnt create new program");
            }
            return 0;
        }

        glAttachShader(programObjectID, vertexShaderID);
        glAttachShader(programObjectID, fragmentShaderID);
        glLinkProgram(programObjectID);

        final int[] linkStatus = new int[1];
        glGetProgramiv(programObjectID, GL_LINK_STATUS, linkStatus, 0);
        if(LoggerConfig.ON){
            // Print program info
            Log.v(TAG, "Results of linking program:\n"+glGetShaderInfoLog(programObjectID));
        }

        if (linkStatus[0]==0){
            // If it failed delete the program obj
            glDeleteProgram(programObjectID);
            if (LoggerConfig.ON){
                Log.w(TAG, "Linking program failed");
            }
            return 0;
        }

        return programObjectID;
    }
    public static boolean validateProgram(int programObjectID){
        glValidateProgram(programObjectID);

        final int[] validateStatus = new int[1];
        glGetProgramiv(programObjectID, GL_VALIDATE_STATUS, validateStatus, 0);
        Log.v(TAG, "Results of validating program: "+validateStatus[0]+"\nLog: "+glGetProgramInfoLog(programObjectID));
        return validateStatus[0] != 0;
    }
}
