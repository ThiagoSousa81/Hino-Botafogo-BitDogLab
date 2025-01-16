#define DO 0
#define REb 1
#define RE 2
#define MIb 3
#define MI 4
#define FA 5
#define SOLb 6
#define SOL 7
#define LAb 8
#define LA 9
#define SIb 10
#define SI 11

#define do 12
#define reb 13
#define re 14
#define mib 15
#define mi 16
#define fa 17
#define solb 18
#define sol 19
#define lab 20
#define la 21
#define sib 22
#define si 23

const float notas[24] = {
    261.625519,
    277.182648,
    293.664734,
    311.126984,
    329.627533,
    349.228241,
    369.994385,
    391.995392,
    415.304688,
    440,
    466.163788,
    493.883301,

    523.251099,
    554.365234,
    587.329529,
    622.253906,
    659.255127,
    698.456482,
    739.988831,
    783.990845,
    830.609375,
    880,
    932.327576,
    987.766602};

const char musica[] = {
    FA, FA, SIb, SIb, do, re, LA, LA,
    SIb, do, SOL, SOL, FA, SOL, SOL, FA, SOL, FA, LA, SOL,

    FA, FA, LA, LA, SIb, do, SOL, SOL,
    LA, SIb, FA, FA, do, re, do, SI, do, FA,

    FA, SOL, LA, SIb, do, re, do, SIb, SOL, SIb,
    SOL, SOL, do, re, mi, re, do, LA, do,

    FA, SIb, do, SIb, SOL, do, do,
    do, re, do, re, mib,
    mib, re, do, FA, SIb};

const int tempos_off[] = {
194314,
193271,
212358,
216686,
218190,
250482,
215839,
220852,
219293,
258888,
277035,
167749,
181921,
262126,
190068,
156896,
167814,
155907,
183453,
241263,
182624,
165687,
209273,
208070,
228435,
219001,
220944,
252194,
243330,
255024,
212375,
181504,
149064,
153086,
154220,
169555,
224882,
145369,
187233,
204307,
245571,
246397,
200709,
198183,
155901,
158117,
176260,
221173,
120782,
208998,
230035,
216509,
206067,
156892,
148523,
173262,
249148,
223286,
217373,
162159,
134691,
174012,
197735,
205494,
163483,
127238,
145798,
178325,
245787,
182936,
129484,
155288,
184928,
0,
};
const int tempos_on[] = {
100055,
100005,
356402,
294792,
320747,
305048,
355481,
320853,
308782,
309847,
278868,
100005,
100005,
253820,
100005,
100005,
100005,
100005,
100005,
600791,
100006,
100005,
361438,
337487,
334709,
306064,
342731,
311295,
293245,
286705,
642123,
100005,
100005,
100005,
100004,
100005,
353855,
100004,
100005,
344333,
283075,
845394,
308885,
325317,
100005,
100005,
100004,
590775,
100005,
100005,
839234,
308214,
313848,
100005,
100005,
100005,
584835,
317832,
832255,
100005,
100005,
100004,
335705,
300653,
100005,
100004,
100005,
100005,
738570,
104106,
100005,
100005,
100005,
1373966,
};





