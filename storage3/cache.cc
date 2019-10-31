#include <cstdlib>
#include <iostream>
#include <string>
#include <getopt.h>

using namespace std;

#define NUM_MOVIES 50
string movies[NUM_MOVIES] = {
    "00:RESERVED",
    "01:The Exorcist",
    "02:The Shining",
    "03:The Texas Chain Saw Massacre",
    "04:Alien",
    "05:Psycho",
    "06:The Thing",
    "07:Rosemary's Baby",
    "08:Halloween",
    "09:Dawn of the Dead",
    "10:Jaws",
    "11:Suspira",
    "12:Night of the Living Dead",
    "13:Don't Look Now",
    "14:The Innocents",
    "15:Carrie",
    "16:An American Werewolf in London",
    "17:Evil Dead II",
    "18:The Fly",
    "19:Let the Right One In",
    "20:A Nightmare on Elm Street",
    "21:Audition",
    "22:The Haunting",
    "23:Nosferatu",
    "24:Freaks",
    "25:The Omen",
    "26:Poltergeist",
    "27:The Blair Witch Project",
    "28:The Evil Dead",
    "29:The Birds",
    "30:The Changeling",
    "31:Videodrome",
    "32:Cat People",
    "33:Hereditary",
    "34:Bride of Frankenstein",
    "35:Carnival of Souls",
    "36:The Wicker Man",
    "37:Frankenstein",
    "38:Eyes Without a Face",
    "39:Cannibal Holocaust",
    "40:Jacob's Ladder",
    "41:Possession",
    "42:The Devil's Backbone",
    "43:Hour of the Wolf",
    "44:The Tenant",
    "45:The Silence of the Lambs",
    "46:The Others",
    "47:Dead of Night",
    "48:Invasion of the Body Snatchers",
    "49:Ring"
};

//
// Global variables
int nrefs = 0;     // number of references
int nhits = 0;     // number of hits

//
// Definition of a cache slot
//
struct cache_slot {
    bool valid;       // if false, slot is empty
    int mindex;       // if slot valid, this is an index into movies array
    int last_access;  // used to implement LRU replacement

    // NOTE: no data field in this toy cache because we are only simulating
    // the behavior of the cache, not actually moving data between levels
    // of the memory hierarchy!

    cache_slot() { valid = false; mindex = 0; last_access = -1;}
    ~cache_slot() {}
};

//
// Definition and implementation of a cache
//
struct cache {
    // the following define the organization of cache we simulate
    int nslots;
    bool is_direct_mapped;
    char replacement;       // if fully associative, the replacement algo

    cache_slot* slot;       // the array of slots comprising the cache

    cache(int nslots, bool dm = false, char r_algo = 'r');
    ~cache();

    // operations when the cache is presented with a reference
    void fill(int r);
    int lookup(int r);

    // helps us visualize the cache
    void print();
};

cache::cache(int n, bool dm, char r_algo) {
    nslots = n;
    slot = new cache_slot[n];
    is_direct_mapped = dm;
    replacement = r_algo;
}

cache::~cache() {
    delete[] slot;
}

void cache::fill(int r) {
    int slot_index;
    if (this->is_direct_mapped) {
        // For a direct-mapped cache, replacement is simple, since
        // each address can reside in only a single slot.
        slot_index = r % this->nslots;
    } else {
        // For a fully-associative cache, replacement depends upon
        // the replacement algorithm we have choosen to use.

        switch (this->replacement) {
        case 'r':
            // Replacement: random
            slot_index = rand() % this->nslots;
            break;

        case 'l':
            // Replacement: LRU
            slot_index = 0;
            for (int i = 1; i < this->nslots; i++) {
                if (this->slot[i].last_access < this->slot[slot_index].last_access) {
                    slot_index = i;
                }
            }
            break;

        case 'o':
            // Replacement: round robin
            slot_index = (nrefs - nhits) % this->nslots;
            break;

        default:
            fprintf(stderr, "Unknown replacement algorithm %c\n", this->replacement);
            exit(1);
        }
    }

    this->slot[slot_index].last_access = nrefs;
    this->slot[slot_index].mindex = r;
    this->slot[slot_index].valid = true;
}

int cache::lookup(int r) {
    if (this->is_direct_mapped) {
        // direct-mapped lookup -- check just one slot
        int slot_index = r % this->nslots;
        if (this->slot[slot_index].valid &&
            this->slot[slot_index].mindex == r) {
            // hit
            return 1;
        }
        // else miss
        this->fill(r);
        return 0;
    }

    // else lookup for fully associative cache
    for (int i = 0; i < this->nslots; i++) {  // check every slot
        if (this->slot[i].valid &&
            this->slot[i].mindex == r) {
            // hit

            // bookkeeping for LRU replacement
            this->slot[i].last_access = nrefs;  // LRU

            return 1;
        }
    }
    // else miss
    this->fill(r);
    return 0;
}

void cache::print() {
    printf("\n");
    printf("   +------------------\n");
    for (int i = 0; i < this->nslots; i++) {
        printf("s%d | %c | %s\n", i,
               this->slot[i].valid ? 'v' : ' ',
               this->slot[i].valid ? movies[this->slot[i].mindex].c_str() : " ");
        printf("   +------------------\n");
    }
    printf("\n");
}


int ref_string[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5, -1};

int main (int argc, char* argv[]) {
    int nslots = 4;   // default number of slots in the cache
    bool is_direct_mapped = true;   // defaults to a direct-mapped cache
    char replacement = 'r';         // defaults to random replacement
    bool quiet_mode = false;        // defaults to showing the cache simulation

    // Read options
    int opt;
    while ((opt = getopt(argc, argv, "df:qs:")) != -1) {
        switch (opt) {
        case 'd':
            is_direct_mapped = true;
            break;
        case 'f':
            is_direct_mapped = false;
            replacement = optarg[0];  // Valid values: r = random,
                                      // l = LRU, o = round robin
            break;
        case 'q':
            quiet_mode = true;
            break;
        case 's':
            nslots = strtol(optarg, NULL, 0);
            break;
        default:
            fprintf(stderr,
                    "Usage: ./cache [-d] [-f REP_ALGO] [-q] [-s NUM_SLOTS]\n"
                    "where -d specifies a direct-mapped cache\n"
                    "      -f specifies a fully associative cache\n"
                    "      -q specifies quiet mode\n"
                    "      -s specifies the number of slots in the cache\n");
            exit(1);
        }
    }

    // Create the cache
    cache my_cache(nslots, is_direct_mapped, replacement);

    // Run ref_string through direct-mapped cache
    while (ref_string[nrefs] > 0) {
        int hit = my_cache.lookup(ref_string[nrefs]);

        nhits += hit;
        nrefs++;

        if (quiet_mode) {
            continue;
        } // else
        if (hit) {
            printf("#%d: ref %d was a HIT!\n", nrefs, ref_string[nrefs-1]);
        } else {
            printf("#%d: ref %d was a MISS!\n", nrefs, ref_string[nrefs-1]);
            my_cache.print();
        }
    }

    printf("\nThe %d-slot, %s cache %shad\n"
           "%d hits in %d references.\n\n",
           nslots,
           is_direct_mapped ? "direct-mapped" : "fully associative",
           is_direct_mapped ? "" : (replacement == 'r' ? "(random replacment) "
                                    : (replacement == 'l' ? "(LRU replacement) "
                                       : "(round-robin replacement) ")),
           nhits,
           nrefs);

    return 0;
}
