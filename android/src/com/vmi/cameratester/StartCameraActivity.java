package com.vmi.cameratester;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.v4.content.FileProvider;  //In gradle you need "compile 'com.android.support:support-v4:25.3.1'"
import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.net.Uri;
import android.util.Log;
import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Set;

//This is wrong: public class StartCameraActivity extends org.qtproject.qt5.android.bindings.QtActivity {

//This is right:
public class StartCameraActivity extends android.app.Activity {

    private static final String TAG = StartCameraActivity.class.getName();
    public String lastCameraFileUri;
    static final int REQUEST_OPEN_CAMERA =1;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.d(TAG, "Enters StartCameraActivity.onCreate");
        Log.d(TAG, "getApplicationContext().getPackageName(): " + getApplicationContext().getPackageName());

        dispatchTakePictureIntent();  //Den här har någon annan gjort och jag har modifierat den lite.
    }

    //Denna anropas alltid när en activity är typ klar. Den funkar osm ett slot i QT.
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        if  (requestCode == REQUEST_OPEN_CAMERA) {

            //Check if file exists
            File presumptiveFile = new File(lastCameraFileUri);

            Log.d(TAG, "lastCameraFileUri          : " + lastCameraFileUri);
            Log.d(TAG, "presumptiveFile.toString() : " + presumptiveFile.toString());
            Log.d(TAG, "Does it exists?            : " + presumptiveFile.exists());

            Intent output = new Intent();

            if (presumptiveFile.exists())
                output.putExtra("photoURI", lastCameraFileUri); //Send an uri back through the intent-extra-pipeline
            else
                output.putExtra("photoURI", "NO PHOTO WAS TAKEN");

            setResult(RESULT_OK, output);
            finish();

        }
        else
        {
            Log.d(TAG, "This will never print?");
        }
    }
    //This will start up the Native OEM-camera
    private void dispatchTakePictureIntent() {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);

        // Ensure that there’s a camera activity to handle the intent
        if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
            // Create the File where the photo should go

            File photoFile = null;
            try {
                photoFile = createImageFile();
            } catch (IOException ex) {
                // Error occurred while creating the File
                Log.d(TAG, "ERROR ex.getLocalizedMessage() : " + ex.getLocalizedMessage());
                Log.d(TAG, "ERROR ex.getMessage()          : " + ex.getMessage());
            }

            // Continue only if the File was successfully created
            if (photoFile != null) {
                //The getApplicationContext().getPackageName() should return com.vmi;

                Uri photoURI = FileProvider.getUriForFile(this,
                        getApplicationContext().getPackageName() + ".fileprovider", photoFile);

                lastCameraFileUri = photoFile.toString();

                takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, photoURI);
                startActivityForResult(takePictureIntent, REQUEST_OPEN_CAMERA);

            }
        } else {
            Log.d(TAG, "ERROR. Problems with your camera?!");
        }
    }

    private File createImageFile() throws IOException {
        // Create an image file name
        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());

        String imageFileName = "XBalancer" + timeStamp;

        //Here we get the path where all pictures are stored
        File storageDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);

        File image = new File(storageDir, imageFileName + ".jpg");

        Log.d(TAG, "imageFileName: " + imageFileName);

        Log.d(TAG, "image.toString(): " + image.toString());
        return image;
    }


  @Override
  protected void onStop() {
      Log.w(TAG, "Activity stopped");

      super.onStop();
  }

  @Override
  protected void onDestroy() {
      Log.w(TAG, "Activity destroyed");

      super.onDestroy();
  }


}
