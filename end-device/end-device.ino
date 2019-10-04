/* == Wiring guideline == 

    name | pin | function
    -----|-----|---------
    CLK  | 13  | clock
    -----|-----|---------
    SEL  | 12  | select
    -----|-----|---------
    DATA |[2,5]| data, the order of data must be inverse than the order of physical data
    ---------------------

   ====================== */


/* == definitions == */
#define CLK 13 // Pin of clock
#define BAUD 9600 // The baud rate of serial
#define SEL 12 // Pin of select
#define DATA 2 // Last pin of data, the n wide data line must be wired from 2+n-1 to 2 (inverse the order)
#define WIDE 4 // The wide of data bus
#define DEBUG  // Set the debug mode (Modify DEBUG to _DEBUG to disable the debug functions)

/* ================= */

/* == Global variable == */
int clk;    // The clock frequence (HZ)
int r_size; // The size of row of tile
int c_size; // The size of column of tile
int len;    // The length of tile
char *tile; // The array of the tile
/* 
 * Two solutions
 * 1. Use the lower 4 bits to save the value and reserve the upper 4 bits
 * 2. Use the lower and upper 4 bits to save the value of different tile 
 * Now using solution 1
 */

/* ===================== */


#ifdef DEBUG

void wait_clk (unsigned int start)
{
    unsigned int _end
    do {
        _end = millis ();
    } while (_end - start < wait);
}

#else

void wait_clk (unsigned int start) {}

#endif


inline void clk_on()
{
    digitalWrite (CLK, 1);
}

inline void clk_off()
{
    digitalWrite (CLK, 0);
}

// To initialize the size of tile
// suppose the value will be assign form gateway 
char *init_size()
{
    char *arr = NULL;
    r_size = 1;
    c_size = 2;
    len = r_size * c_size;
    while (!arr)
        arr = malloc (r_size * c_size);
    return arr;
}

void set_clk (int t)
{
    clk = t;
    wait = 1.0/clk * 100;
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
    for (int i=0; i<WIDE; i++)
        pinMode (DATA+i, INPUT);
    Serial.begin (BAUD);
    tile = init_size ();
    set_clk (1);
    Serial.println ("Initialized!");
    Serial.println ("Clock: " + clk + " HZ");
    Serial.println ("Tile size: " + r_size + " * " + c_size);
}

void loop() 
{
    unsigned int sTime;
    sTime = millis ();
    digitalWrite (SEL, 1);
    clk_on ();
    wait_clk (sTime);
    clk_off ();
}
