#define  a3f    208     // 208 Hz
#define  b3f    233     // 233 Hz
#define  b3     247     // 247 Hz
#define  c4     261     // 261 Hz MIDDLE C
#define  c4s    277     // 277 Hz
#define  e4f    311     // 311 Hz    
#define  f4     349     // 349 Hz 
#define  a4f    415     // 415 Hz  
#define  b4f    466     // 466 Hz 
#define  b4     493     // 493 Hz 
#define  c5     523     // 523 Hz 
#define  c5s    554     // 554 Hz
#define  e5f    622     // 622 Hz  
#define  f5     698     // 698 Hz 
#define  f5s    740     // 740 Hz
#define  a5f    831     // 831 Hz 

#define rest    -1

int piezo = 8; 
int led = LED_BUILTIN; 

volatile int beatlength = 100; // determines tempo
float beatseparationconstant = 0.3;

int threshold;

int b; // song index


boolean flag;

int song1_intro_melody[] =
{c5s, e5f, e5f, f5, a5f, f5s, f5, e5f, c5s, e5f, rest, a4f, a4f};

int song1_intro_rhythmn[] =
{6, 10, 6, 6, 1, 1, 1, 1, 6, 10, 4, 2, 10};

int light = 8;
int sensor = 10;
boolean lightToggle = false;
boolean readyToToggle = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(light, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(piezo, OUTPUT);
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);
  Serial.begin(9600);
  flag = true;

  b = 0;

}

void play() {
  int notelength;
  notelength = beatlength * song1_intro_rhythmn[b];
  if (song1_intro_melody[b] > 0) {
    digitalWrite(led, HIGH);
    tone(piezo, song1_intro_melody[b], notelength);
  }
  b++;
  if (b >= sizeof(song1_intro_melody) / sizeof(int)) {
    flag = false;
    b = 0;

  }
  delay(notelength);
  noTone(piezo);
  digitalWrite(led, LOW);
  delay(notelength * beatseparationconstant);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(sensor) == HIGH) {
    if (readyToToggle && !flag){
       // play next step in song
       readyToToggle = false;
       flag = true;
    }
    
  } else if(!flag) {
    
    if (!readyToToggle) {
      readyToToggle = true;
    }
    
  }

 
  if (flag == true) {
      play();
  }
  
}
