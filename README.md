# face  
And now ladies and germs, the moment you've all been waiting for.... We will be running face recognition on the BBG!  
Install opencv with the following command...  
```
sudo apt-get install libopencv-dev
```  
Now you should be able to compile your programs with the Face module in this repo with the following command...  
```  
g++ face.cpp main.cpp -o main `pkg-config --cflags --libs opencv4`  
```  
**FACE.CPP**  
Contains Face_initialize() for reading sample list in training.csv, and training the model with the 41 test subjects in the training-data folder.  
Contains Face_predict() which reads in an image and predicts it's class. The image must be a grayscale 92x112 .pgm file. Returns 1 on success and 0 on failure. We may need to change the threshold at some point.   
  
**WRITECSV.PY**  
Contains a script that prints all the test image paths to terminal. Copy and paste the output into **training.csv**. Alternatively, you can find and replace the path in the csv with the path you will be using on your own device.
