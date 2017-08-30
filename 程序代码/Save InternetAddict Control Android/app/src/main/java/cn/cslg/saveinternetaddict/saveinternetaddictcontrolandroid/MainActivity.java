package cn.cslg.saveinternetaddict.saveinternetaddictcontrolandroid;

import android.support.v7.app.AppCompatActivity;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;
import android.view.View;
import android.os.Bundle;

import java.util.List;
import java.util.Arrays;

public class MainActivity extends AppCompatActivity {
    private String[] handle = {"关机", "重启", "注销"};
    private String[] info = {"强制处理无警告", "非强制处理含提示"};

    private Spinner spinner1, spinner2;
    private EditText editText1, editText2;

    private void initSpinner() {
        List<String> dataList1 = Arrays.asList(this.handle);
        List<String> dataList2 = Arrays.asList(this.info);
        ArrayAdapter<String> arrayAdapter1 = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, dataList1);
        ArrayAdapter<String> arrayAdapter2 = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, dataList2);
        arrayAdapter1.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        arrayAdapter2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        this.spinner1.setAdapter(arrayAdapter1);
        this.spinner2.setAdapter(arrayAdapter2);
    }

    private boolean checkIP(String ip) {
        String[] ipList = ip.split("\\.");
        if (ipList.length != 4) {
            return false;
        }

        for (int i = 0; i < 4; ++i) {
            int tempNumber = this.getTime(ipList[i]);
            if (tempNumber < 0 | tempNumber > 255) {
                return false;
            }
        }

        return true;
    }

    private int getTime(String time) {
        try {
            return Integer.parseInt(time);
        } catch (NumberFormatException e) {
            return 0;
        }
    }

    private int getID(String str, String[] strList) {
        for (int i = 0; i < strList.length; ++i) {
            if (str.equals(strList[i])) {
                return i + 1;
            }
        }
        return 1;
    }

    private void sentMessage(String ip, String messageInfo) {
        if (NetThread.state != 0) {
            Toast.makeText(this, "上一次处理还未结束!", Toast.LENGTH_LONG);
        } else {
            NetThread netThread = new NetThread(ip, messageInfo);
            netThread.start();
            Toast.makeText(this, "消息已经发送!", Toast.LENGTH_LONG);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.spinner1 = (Spinner) findViewById(R.id.spinner1);
        this.spinner2 = (Spinner) findViewById(R.id.spinner2);
        this.editText1 = (EditText) findViewById(R.id.editText1);
        this.editText2 = (EditText) findViewById(R.id.editText2);

        this.editText1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                editText1.setText("");
            }
        });
        this.editText2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                editText2.setText("0");
            }
        });

        this.initSpinner();
    }

    public void SaveIt(View view) {
        String ip = this.editText1.getText().toString();
        String time = this.editText2.getText().toString();

        if (!checkIP(ip)) {
            Toast.makeText(this,"请输入正确的IP！", Toast.LENGTH_LONG).show();
            return ;
        }
        int handleTime = this.getTime(time);

        String handle = this.spinner1.getSelectedItem().toString();
        String info = this.spinner2.getSelectedItem().toString();

        int target = this.getID(handle, this.handle);
        int fast = this.getID(info, this.info);
        String messageInfo = "" + target + fast + handleTime;
        this.sentMessage(ip, messageInfo);
    }
}
