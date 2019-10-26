/* == tile form == 
 *  
 *  -----------
 *  | b0 | b1 | 
 *  ----------- 
 *  | b2 | b3 |
 *  -----------
 *  
 */

/* == Wiring guideline == 

    name | pin | function
    -----|-----|---------
    CLK  | 13  | clock
    -----|-----|---------
    SEL  | 12  | select
    -----|-----|---------
    DATA |[2,5]| data, b0 > 2, b1 > 3, b2 > 4, b3 > 5
    ---------------------

   ====================== */


/* == definitions == */
#define CLK 13 // Pin of clock
#define SEL 12 // Pin of select
#define DATA 2 // Last pin of data, the n wide data line must be wired from 2+n-1 to 2 (inverse the order)
#define CONNECT A0 // Is wifi connecting
#define WIDE 4 // The wide of data bus, code must be modify when wide over 8 bits
#define FREQ 100   // The frequence of clock
#define BAUD 115200 // The baud rate of serial
//#define DEBUG  // Set the debug mode (Modify DEBUG to _DEBUG to disable the debug functions)

/* ================= */

/* == Global variable == */
int clk;    // The clock frequence (HZ)
int cyc;  // The cycle of the clock (millisecend)
unsigned int cStart; // Current cycle start time
int r_size; // The size of row of tile
int c_size; // The size of column of tile
int len;    // The length of tile
char *tile; // Senser data tile by tile


/* ===================== */

inline void sel_on()
{
    digitalWrite (SEL, 0);
}

//Select OFF
inline void sel_off()
{
    char ret;
    digitalWrite (SEL, 1);
    ret = 'A';
    do {
        if (Serial.available()) {
            ret = Serial.read ();
        }
    } while (ret != 'E');
}

inline void exe_clk()
{   
    digitalWrite (CLK, 1);
    delay (cyc);
    digitalWrite (CLK, 0);
    delay (cyc);
}

inline void wait_wifi()
{
    while (analogRead (CONNECT) < 400);
}

// To initialize the size of tile
// suppose the value will be assign form gateway 
char *init_size()
{
    char *arr = NULL;

    r_size = 3;
    c_size = 3;
    len = r_size * c_size;
    arr = (char *)malloc (len);
    memset (tile, 0, len);

    return arr;
}

void set_clk (int t)
{
    clk = t;
    cyc = (int)(1.0/clk * 1000)>>1;
}

// Must to be modify if data wide over 8 bits
char get_data ()
{
    char d;
    d = 0;
    for (int i=0; i<WIDE; i++) {
        d <<= 1;
        d |= digitalRead (DATA + i);
    }
    return d;  
}

void setup() 
{
    pinMode (CLK, OUTPUT);
    pinMode (SEL, OUTPUT);
    pinMode (CONNECT, INPUT);
    for (int i=0; i<WIDE; i++)
        pinMode (DATA+i, INPUT);

    Serial.begin (BAUD);
    init_size ();
    set_clk (FREQ);
    tile = init_size ();
    wait_wifi ();
}

void loop() 
{
    //Serial.println ("\n==== Loop ====");
    static int n = 0;
    Serial.print ('S');
    for (int i=0; i<r_size; i++) {
        for (int o=0; o<c_size; o++) {
            char buff;
            int desti;
            buff = get_data () + 'A';
            //buff = 'A' + n;
            Serial.print (buff);
            exe_clk ();
        }
    }
    sel_on ();
    exe_clk ();
    sel_off ();
    delay (5000);
    n++;
    n %= 16;
}
