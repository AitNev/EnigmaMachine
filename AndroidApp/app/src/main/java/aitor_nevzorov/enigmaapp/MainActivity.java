package aitor_nevzorov.enigmaapp;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;


public class MainActivity extends AppCompatActivity {
    //Declaramos Los Componentes
    Button btnVinculados,btnBuscar;
    ListView listaDispositivos;
    //Bluetooth
    private BluetoothAdapter myBluetooth = null;
    private Set<BluetoothDevice> dispVinculados;
    public static String EXTRA_ADDRESS = "device_address";
    ArrayList list = new ArrayList();
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //Declaramos nuestros componenetes ralcionandolos con los del layout
        btnVinculados = (Button)findViewById(R.id.button);
        btnBuscar = (Button)findViewById(R.id.btnSearch);
        listaDispositivos = (ListView)findViewById(R.id.listView);

        //Comprobamos que el dispositivo tiene bluetooth
        myBluetooth = BluetoothAdapter.getDefaultAdapter();

        if(myBluetooth == null)
        {
            //Mostramos un mensaje, indicando al usuario que no tiene conexión bluetooth disponible
            Toast.makeText(getApplicationContext(), "Bluetooth no disponible", Toast.LENGTH_LONG).show();

            //finalizamos la aplicación
            finish();
        }
        else if(!myBluetooth.isEnabled())
        {
            //Preguntamos al usuario si desea encender el bluetooth
            Intent turnBTon = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(turnBTon,1);
        }

        btnVinculados.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                listaDispositivosvinculados();
            }
        });
        btnBuscar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                busquedaDispositivos();
                if(!myBluetooth.startDiscovery()){
                    Toast.makeText(getApplicationContext(), "No se puede vision", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
    private void busquedaDispositivos() {

        final BroadcastReceiver mReciver = new BroadcastReceiver() {

            @Override
            public void onReceive(Context context, Intent intent) {
                String action = intent.getAction();
                //When discovery finds a device
                if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                    //Get the device object from intent
                    BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                    //
                    String s =device.getName() + "-Sheached\n" + device.getAddress();
                    list.add(s);
                    Toast.makeText(getApplicationContext() , s, Toast.LENGTH_LONG).show();

                }
                else{
                    Toast.makeText(getApplicationContext() , "No Se ha encontrado", Toast.LENGTH_LONG).show();
                }
            }
        };
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        registerReceiver(mReciver, filter);
        //myBluetooth.cancelDiscovery();
        //Imprimimos los dispositivos
        Toast.makeText(getApplicationContext() , "No Se ha encontrado", Toast.LENGTH_LONG).show();

        final ArrayAdapter adapter = new ArrayAdapter(this,android.R.layout.simple_list_item_1, list);
        listaDispositivos.setAdapter(adapter);
        listaDispositivos.setOnItemClickListener(myListClickListener);
    }
    private void listaDispositivosvinculados()
    {
        dispVinculados = myBluetooth.getBondedDevices();


        if (dispVinculados.size()>0)
        {
            for(BluetoothDevice bt : dispVinculados)
            {
                list.add(bt.getName() + "\n" + bt.getAddress()); //Obtenemos los nombres y direcciones MAC de los disp. vinculados
            }
        }
        else
        {
            Toast.makeText(getApplicationContext(), "No se han encontrado dispositivos ", Toast.LENGTH_LONG).show();
        }


        final ArrayAdapter adapter = new ArrayAdapter(this,android.R.layout.simple_list_item_1, list);
        listaDispositivos.setAdapter(adapter);
        listaDispositivos.setOnItemClickListener(myListClickListener);

    }

    private AdapterView.OnItemClickListener myListClickListener = new AdapterView.OnItemClickListener()
    {
        public void onItemClick (AdapterView<?> av, View v, int arg2, long arg3)
        {
            // Get the device MAC address, the last 17 chars in the View
            String info = ((TextView) v).getText().toString();
            String address = info.substring(info.length() - 17);

            // Make an intent to start next activity.
            Intent i = new Intent(MainActivity.this, ledControl.class);

            //Change the activity.
            i.putExtra(EXTRA_ADDRESS, address); //this will be received at ledControl (class) Activity
            startActivity(i);
        }
    };


    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}