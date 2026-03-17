#ifndef DS1307RTC_h
#define DS1307RTC_h

//definicao dos endereÃ§os
#define SEC     0
#define MIN     1
#define HOUR    2
#define WEEKDAY 3
#define DAY     4
#define MONTH   5
#define YEAR    6

#define ALARM_LOW_FIRST_BYTE 0x10
#define ALARM_LOW_SECOND_BYTE 0x11
#define ALARM_HIGH_FIRST_BYTE 0x17
#define ALARM_HIGH_SECOND_BYTE 0x18
#define LANGUAGE 0x14

//funcoes do DS1307
void dsInit(void);
void dsStartClock(void);
//void dsStopClock(void);
int dec2bcd(int value);
int bcd2dec(int value);
void dsWriteData(unsigned char value, int address);
int dsReadData(int address);
  
//funcoes de leitura/escrita dos niveis do alarme
int dsGetAlarmUpper();
void dsSetAlarmUpper(int value);

int dsGetAlarmLower();
void dsSetAlarmLower(int value);


//funções de leitura/escrita simplificadas
#define getSeconds()  (bcd2dec(dsReadData(SEC)& 0x7f))
#define getMinutes()  (bcd2dec(dsReadData(MIN)& 0x7f))
#define getHours()    (bcd2dec(dsReadData(HOUR)& 0x7f))
#define getWeekDay()  (bcd2dec(dsReadData(WEEKDAY)& 0x07))
#define getDays()     (bcd2dec(dsReadData(DAY)& 0x7f))
#define getMonths()   (bcd2dec(dsReadData(MONTH)& 0x1f))
#define getYears()    (bcd2dec(dsReadData(YEAR)& 0xff))

#define setSeconds(v) (dsWriteData(dec2bcd(v)|0x80,SEC))
#define setMinutes(v) (dsWriteData(dec2bcd(v),MIN))
#define setHours(v)   (dsWriteData(dec2bcd(v),HOUR))
#define setWeekDay(v) (dsWriteData(dec2bcd(v),WEEKDAY))
#define setDays(v)    (dsWriteData(dec2bcd(v),DAY))
#define setMonths(v)  (dsWriteData(dec2bcd(v),MONTH))
#define setYears(v)   (dsWriteData(dec2bcd(v),YEAR))

//funcoes de leitura/escrita das variaveis
#define dsGetLanguage() (bcd2dec(dsReadData(LANGUAGE) & 0xff))
#define dsSetLanguage(v) (dsWriteData(dec2bcd(v), LANGUAGE))

#endif
