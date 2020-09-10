package com.example.authome;

import android.app.Dialog;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;
import com.google.android.material.tabs.TabLayout;

import androidx.viewpager.widget.ViewPager;
import androidx.appcompat.app.AppCompatActivity;

import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

import com.example.authome.ui.main.SectionsPagerAdapter;
import com.google.firebase.firestore.FirebaseFirestore;

public class MainActivity extends AppCompatActivity {

    Dialog add_device_dialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        SectionsPagerAdapter sectionsPagerAdapter = new SectionsPagerAdapter(this, getSupportFragmentManager());
        ViewPager viewPager = findViewById(R.id.view_pager);
        viewPager.setAdapter(sectionsPagerAdapter);
        TabLayout tabs = findViewById(R.id.tabs);
        tabs.setupWithViewPager(viewPager);
        FloatingActionButton fab = findViewById(R.id.fab);

        add_device_dialog = new Dialog(this);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                popout_add_device_dialog(view);
            }
        });
    }

    //https://www.youtube.com/watch?v=0DH2tZjJtm0
    public void popout_add_device_dialog(View v)
    {
        FloatingActionButton close;
        Button receive;
        Button receive2;
        Button receive3;
        add_device_dialog.setContentView(R.layout.add_device_popout);
        close = add_device_dialog.findViewById(R.id.close);
        receive = add_device_dialog.findViewById(R.id.button);
        receive2 = add_device_dialog.findViewById(R.id.button2);
        receive3 = add_device_dialog.findViewById(R.id.button3);
        close.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                add_device_dialog.dismiss();
            }
        });
        receive.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view) {
                FirebaseFirestore db = FirebaseFirestore.getInstance();
                db.collection("user_0").document("doc").update("On","1");
            }

        });
        receive2.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view) {
                FirebaseFirestore db = FirebaseFirestore.getInstance();
                db.collection("user_0").document("doc").update("On","0");
            }

        });
        receive3.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view) {
                FirebaseFirestore db = FirebaseFirestore.getInstance();
                db.collection("user_0").document("doc").update("reset","1");
            }

        });
        add_device_dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        add_device_dialog.show();
    }


}