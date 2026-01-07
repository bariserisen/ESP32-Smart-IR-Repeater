#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

// --- PIN AYARLARI ---
const uint16_t kRecvPin = 15;  // IR Alıcı (Göz) D15'te
const uint16_t kIrLedPin = 4;  // IR LED (Megafon) D4'te

// --- NESNELER ---
IRrecv irrecv(kRecvPin);
IRsend irsend(kIrLedPin);
decode_results results;

// --- KAYDETTİĞİMİZ KODLAR (SAMSUNG) ---
#define KOD_POWER    0xE0E040BF
#define KOD_SES_AC   0xE0E0E01F
#define KOD_SES_KIS  0xE0E0D02F

void setup() {
  Serial.begin(115200);
  
  irrecv.enableIRIn();  // Alıcıyı başlat (Kulakları aç)
  irsend.begin();       // Vericiyi başlat (Megafonu hazırla)
  
  Serial.println("--- Sinyal Guclendirici Aktif ---");
  Serial.println("Kumandayi bana tut, ben TV'ye bagiracagim!");
}

void loop() {
  // Eğer bir sinyal geldiyse...
  if (irrecv.decode(&results)) {
    
    // Gelen sinyalin değerini al
    uint64_t gelenKod = results.value;

    // --- SİNYAL ANALİZİ VE TEKRARLAMA ---
    if (gelenKod == KOD_POWER) {
      Serial.println("Tespit: POWER -> Guclendirip gonderiliyor...");
      // DÜZELTME BURADA YAPILDI: send(ProtokolTipi, Kod, Bit)
      irsend.send(SAMSUNG, KOD_POWER, 32); 
    }
    else if (gelenKod == KOD_SES_AC) {
      Serial.println("Tespit: SES AC -> Guclendirip gonderiliyor...");
      irsend.send(SAMSUNG, KOD_SES_AC, 32);
    }
    else if (gelenKod == KOD_SES_KIS) {
      Serial.println("Tespit: SES KIS -> Guclendirip gonderiliyor...");
      irsend.send(SAMSUNG, KOD_SES_KIS, 32);
    }
    else {
      // Tanımadığımız bir tuşsa sadece ekrana yaz
      Serial.print("Tanimlanmamis Kod: ");
      serialPrintUint64(gelenKod, HEX);
      Serial.println("");
    }

    // Gönderme işlemi bitti, tekrar dinlemeye başla
    irrecv.resume(); 
  }
}