package aitor_nevzorov.enigmaapp;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;

public class ledControl extends AppCompatActivity {
/*
    Button buttonA, buttonB, buttonC, buttonD, buttonE, buttonF, buttonG, buttonH, buttonI, buttonJ, buttonK, buttonL, buttonM,
            buttonN, buttonO, buttonP, buttonQ, buttonR, buttonS, buttonT, buttonU, buttonV, buttonW, buttonX, buttonY, buttonZ;
    Button btnDis;
    SeekBar brightness;
    TextView lumn;
    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        address = newint.getStringExtra(MainActivity.EXTRA_ADDRESS); //recivimos la mac address obtenida en la actividad anterior

        setContentView(R.layout.activity_led_control);

        buttonA = (Button)findViewById(R.id.buttonA);
        buttonB = (Button)findViewById(R.id.buttonB);
        buttonC = (Button)findViewById(R.id.buttonC);
        buttonD = (Button)findViewById(R.id.buttonD);
        buttonE = (Button)findViewById(R.id.buttonE);
        buttonF = (Button)findViewById(R.id.buttonF);
        buttonG = (Button)findViewById(R.id.buttonG);
        buttonH = (Button)findViewById(R.id.buttonH);
        buttonI = (Button)findViewById(R.id.buttonI);
        buttonJ = (Button)findViewById(R.id.buttonJ);
        buttonK = (Button)findViewById(R.id.buttonK);
        buttonL = (Button)findViewById(R.id.buttonL);
        buttonM = (Button)findViewById(R.id.buttonM);
        buttonN = (Button)findViewById(R.id.buttonN);
        buttonO = (Button)findViewById(R.id.buttonO);
        buttonP = (Button)findViewById(R.id.buttonP);
        buttonQ = (Button)findViewById(R.id.buttonQ);
        buttonR = (Button)findViewById(R.id.buttonR);
        buttonS = (Button)findViewById(R.id.buttonS);
        buttonT = (Button)findViewById(R.id.buttonT);
        buttonU = (Button)findViewById(R.id.buttonU);
        buttonV = (Button)findViewById(R.id.buttonV);
        buttonW = (Button)findViewById(R.id.buttonW);
        buttonX = (Button)findViewById(R.id.buttonX);
        buttonY = (Button)findViewById(R.id.buttonY);
        buttonZ = (Button)findViewById(R.id.buttonZ);

        btnDis = (Button)findViewById(R.id.btnDisconect);

        new ConnectBT().execute(); //Call the class to connect


        buttonA.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_A\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonB.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_B\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonC.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_C\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonD.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_D\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonE.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_E\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonF.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_F\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonG.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_G\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonH.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_H\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonI.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_I\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonJ.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_J\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonK.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_K\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonL.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_L\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonM.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_M\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonN.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_N\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonO.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_O\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonP.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_P\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonQ.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_Q\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonR.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_R\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonT.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_T\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonU.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_U\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonV.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_V\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonW.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_W\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonX.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_X\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonY.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_Y\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonZ.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_Z\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        btnDis.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Disconnect();
            }
        });

        brightness.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    lumn.setText(String.valueOf(progress));
                    try
                    {
                        btSocket.getOutputStream().write(String.valueOf(progress).getBytes());
                    }
                    catch (IOException e)
                    {

                    }
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void Disconnect()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.close();
            }
            catch (IOException e)
            { msg("Error");}
        }
        finish();

    }
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_led_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true;

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(ledControl.this, "Connecting...", "Please wait!!!");
        }

        @Override
        protected Void doInBackground(Void... devices)
        {
            try
            {
                if (btSocket == null || !isBtConnected)
                {
                    myBluetooth = BluetoothAdapter.getDefaultAdapter();
                    BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//conectamos al dispositivo y chequeamos si esta disponible
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result)
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Conexión Fallida");
                finish();
            }
            else
            {
                msg("Conectado");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }*/

    Button buttonA, buttonB, buttonC, buttonD, buttonE, buttonF, buttonG, buttonH, buttonI, buttonJ, buttonK, buttonL, buttonM,
            buttonN, buttonO, buttonP, buttonQ, buttonR, buttonS, buttonT, buttonU, buttonV, buttonW, buttonX, buttonY, buttonZ;
    Button btnOn, btnOff, btnDis, btnDash;
    SeekBar brightness;
    TextView lumn;
    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        address = newint.getStringExtra(MainActivity.EXTRA_ADDRESS); //recivimos la mac address obtenida en la actividad anterior

        setContentView(R.layout.activity_led_control);

        btnOn = (Button)findViewById(R.id.button2);
        btnOff = (Button)findViewById(R.id.button3);
        btnDis = (Button)findViewById(R.id.button4);
        brightness = (SeekBar)findViewById(R.id.seekBar);
        lumn = (TextView)findViewById(R.id.lumn);

        buttonA = (Button)findViewById(R.id.buttonA);
        buttonB = (Button)findViewById(R.id.buttonB);
        buttonC = (Button)findViewById(R.id.buttonC);
        buttonD = (Button)findViewById(R.id.buttonD);
        buttonE = (Button)findViewById(R.id.buttonE);
        buttonF = (Button)findViewById(R.id.buttonF);
        buttonG = (Button)findViewById(R.id.buttonG);
        buttonH = (Button)findViewById(R.id.buttonH);
        buttonI = (Button)findViewById(R.id.buttonI);
        buttonJ = (Button)findViewById(R.id.buttonJ);
        buttonK = (Button)findViewById(R.id.buttonK);
        buttonL = (Button)findViewById(R.id.buttonL);
        buttonM = (Button)findViewById(R.id.buttonM);
        buttonN = (Button)findViewById(R.id.buttonN);
        buttonO = (Button)findViewById(R.id.buttonO);
        buttonP = (Button)findViewById(R.id.buttonP);
        buttonQ = (Button)findViewById(R.id.buttonQ);
        buttonR = (Button)findViewById(R.id.buttonR);
        buttonS = (Button)findViewById(R.id.buttonS);
        buttonT = (Button)findViewById(R.id.buttonT);
        buttonU = (Button)findViewById(R.id.buttonU);
        buttonV = (Button)findViewById(R.id.buttonV);
        buttonW = (Button)findViewById(R.id.buttonW);
        buttonX = (Button)findViewById(R.id.buttonX);
        buttonY = (Button)findViewById(R.id.buttonY);
        buttonZ = (Button)findViewById(R.id.buttonZ);
        btnDash = (Button)findViewById(R.id.buttonDash);

        new ConnectBT().execute(); //Call the class to connect


        buttonA.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_A\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonB.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_B\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonC.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_C\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonD.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_D\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonE.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_E\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonF.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_F\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonG.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_G\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonH.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_H\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonI.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_I\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonJ.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_J\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonK.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_K\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonL.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_L\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonM.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_M\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonN.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_N\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonO.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_O\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonP.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_P\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonQ.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_Q\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonR.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_R\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonT.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_T\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonS.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_S\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonU.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_U\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonV.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_V\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonW.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_W\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonX.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_X\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonY.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_Y\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        buttonZ.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("E_Z\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        btnDash.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("R___E\n".toString().getBytes());
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        btnOn.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                turnOnLed();
            }
        });

        btnOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                turnOffLed();
            }
        });

        btnDis.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Disconnect();
            }
        });

        brightness.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    lumn.setText(String.valueOf(progress));
                    try
                    {
                        btSocket.getOutputStream().write(String.valueOf(progress).getBytes());
                    }
                    catch (IOException e)
                    {

                    }
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void Disconnect()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.close();
            }
            catch (IOException e)
            { msg("Error");}
        }
        finish();

    }

    private void turnOffLed()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off\n".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void turnOnLed()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("morado\n".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }


    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_led_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true;

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(ledControl.this, "Connecting...", "Please wait!!!");
        }

        @Override
        protected Void doInBackground(Void... devices)
        {
            try
            {
                if (btSocket == null || !isBtConnected)
                {
                    myBluetooth = BluetoothAdapter.getDefaultAdapter();
                    BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//conectamos al dispositivo y chequeamos si esta disponible
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result)
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Conexión Fallida");
                finish();
            }
            else
            {
                msg("Conectado");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
}
