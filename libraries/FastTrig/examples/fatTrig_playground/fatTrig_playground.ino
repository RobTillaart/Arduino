//
//    FILE: fastTrig_playground.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: playground to play with tables.
//    DATE: 2020-09-08

// NOTES
//
// 16 bits is less accurate than 24 bits but still has 5-6 digits OK
//         storage needs 2 bytes per value ==> 182 bytes
//
// 24 bits is as accurate as sin() itself.
//         accuracy wise on par with sin() function (as expected)
//         storage needs 4 bytes per value ==> 364 bytes
//         performance on par with 16 bit
//
// 20 bits is one digit better than 16 bit
//         storage needs 4 bytes per value ==> 364 bytes
//         performance on par with 16 bit
//
// 32 bits makes less sense as float have only 23 bit mantisse
//         maybe to approx. doubles.
//
// TODO questions
// Q: 24 bit per degree or 16 bit per half degree?  Same storage
//
//

#include "Arduino.h"

// tables generated with other sketch.


uint32_t sinTable24[] = {
  0,
  292803, 585516, 878052, 1170319, 1462231, 1753697, 2044628, 2334937, 2624535, 2913333,
  3201244, 3488179, 3774052, 4058776, 4342263, 4624427, 4905183, 5184445, 5462127, 5738146,
  6012416, 6284856, 6555380, 6823908, 7090358, 7354647, 7616696, 7876426, 8133755, 8388608,
  8640904, 8890570, 9137526, 9381700, 9623016, 9861400, 10096780, 10329084, 10558244, 10784186,
  11006844, 11226148, 11442032, 11654434, 11863282, 12068518, 12270078, 12467900, 12661926, 12852092,
  13038346, 13220626, 13398880, 13573052, 13743090, 13908942, 14070558, 14227886, 14380880, 14529494,
  14673684, 14813402, 14948608, 15079260, 15205320, 15326748, 15443508, 15555564, 15662880, 15765426,
  15863168, 15956080, 16044130, 16127294, 16205546, 16278860, 16347216, 16410592, 16468970, 16522332,
  16570660, 16613940, 16652160, 16685308, 16713372, 16736348, 16754222, 16766994, 16774660, 16777215,
};


uint32_t sinTable20[] = {
  0,
  18300, 36595, 54878, 73145, 91389, 109606, 127789, 145933, 164033, 182083,
  200078, 218011, 235878, 253673, 271391, 289026, 306574, 324028, 341383, 358634,
  375776, 392803, 409711, 426494, 443147, 459665, 476043, 492276, 508359, 524288,
  540056, 555660, 571095, 586356, 601438, 616337, 631048, 645567, 659890, 674011,
  687927, 701634, 715126, 728401, 741455, 754282, 766879, 779243, 791370, 803255,
  814896, 826288, 837429, 848315, 858942, 869308, 879409, 889242, 898804, 908093,
  917104, 925837, 934287, 942453, 950332, 957921, 965218, 972222, 978929, 985338,
  991447, 997254, 1002757, 1007955, 1012846, 1017428, 1021700, 1025661, 1029310, 1032645,
  1035665, 1038370, 1040759, 1042831, 1044585, 1046021, 1047138, 1047936, 1048415, 1048575,
};


uint16_t sinTable16[] = {
  0,
  1144, 2287, 3430, 4571, 5712, 6850, 7987, 9121, 10252, 11380,
  12505, 13625, 14742, 15854, 16962, 18064, 19161, 20251, 21336, 22414,
  23486, 24550, 25607, 26655, 27696, 28729, 29752, 30767, 31772, 32768,
  33753, 34728, 35693, 36647, 37589, 38521, 39440, 40347, 41243, 42125,
  42995, 43851, 44695, 45524, 46340, 47142, 47929, 48702, 49460, 50203,
  50930, 51642, 52339, 53019, 53683, 54331, 54962, 55577, 56174, 56755,
  57318, 57864, 58392, 58902, 59395, 59869, 60325, 60763, 61182, 61583,
  61965, 62327, 62671, 62996, 63302, 63588, 63855, 64103, 64331, 64539,
  64728, 64897, 65047, 65176, 65286, 65375, 65445, 65495, 65525, 65535,
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  test_accuracy();
  test_performance();
}

void test_accuracy()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  int cnt16 = 0;
  int cnt24 = 0;
  int equal = 0;

  for (int i = 0; i <= 90; i++)
  {
    float a = sin(i * (PI / 180));
    float b = (1.0 * sinTable16[i]) / 65535;
    float c = (1.0 * sinTable20[i]) / 1048575;
    // float c = (1.0 * sinTable24[i]) / 16777215;
    Serial.print(a, 8);
    Serial.print('\t');
    Serial.print(abs(a - b), 8);
    Serial.print('\t');
    Serial.print(abs(a - c), 8);
    Serial.println();

    if (abs(a - b) < abs(a - c)) cnt16++;
    else if (abs(a - b) > abs(a - c)) cnt24++;
    else equal++;
  }
  Serial.println(cnt16);
  Serial.println(cnt24);
  Serial.println(equal);
}


void test_performance()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint32_t start;
  float sum = 0;

  start = micros();
  for (int i = 0; i <= 90; i++)
  {
    sum += sin(i * PI / 180);
  }
  Serial.println(micros() - start);
  Serial.println(sum, 8);
  delay(10);
  sum = 0;

  start = micros();
  for (int i = 0; i <= 90; i++)
  {
    sum += sinTable16[i] * (1 / 65535.0);
  }
  Serial.println(micros() - start);
  Serial.println(sum, 8);
  delay(10);
  sum = 0;

  start = micros();
  for (int i = 0; i <= 90; i++)
  {
    sum += sinTable20[i] * (1 / 1048575.0);
  }
  Serial.println(micros() - start);
  Serial.println(sum, 8);
  delay(10);
  sum = 0;

  start = micros();
  for (int i = 0; i <= 90; i++)
  {
    sum += sinTable24[i] * (1 / 16777215.0);
  }
  Serial.println(micros() - start);
  Serial.println(sum, 8);
  delay(10);
  sum = 0;
}


void loop()
{
}


// -- END OF FILE --

