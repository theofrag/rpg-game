#RPG COMMAND LINE GAME

 Υπαρχει MAKEFILE στο φακελο programs.Το compile γίνεται απο τον φάκελο programs τρεχοντας `make`.




### ΠΕΡΙΓΡΑΦΗ ΥΛΟΠΟΙΗΣΕΩΝ ###

    ______________________________________________________________________________
    ****************************|##ΑΡΧΕΙΟ Inventory.h|
    
        < Inventory >:  Το Inventory συμβολίζει την αποθήκη όπλων κάθε ήρωα. Μέσα εκεί αποθηκευονται Weapons,Armors,Potions και Spells.
                        Σε κάθε Inventory υπάρχει ένας max αριθμός Items και spells που μπορει να κουβαλήσει καποιος ήρωας.
                        Τα Weapons, Armors, Potion, Spells αποθηκευονται σε αντιστοιχα Vectors, τα οποια είναι private γιατι δεν πρέπει
                        να έχει πρόσβαση ο χρήστης.

                        Στο Inventory γινεται να κανουμε αποθηκευση(store) ενος weapon,potion,armor,spell και να το αφαιρεσουμε
                        (discardWeapon,discardPotion,discardArmor,discardSpell).
                        
                        -Οι συναρτησεις store ειναι overloaded συναρτησεις και παιρνουν ως ορισμα μια αναφορα στο αντιστοιχο αντικειμενο.
                         Αν δεν μπορεσουν να αποθηκευσουν το οπλο λόγω χωρητικοτητας, απλα εκτυπωνουν καταλληλο μηνυμα.
                        
                        -Oι συναρτησεις discardWeapon,discardPotion,discardArmor,discardSpell δεχονται ως ορισμα το ονομα του
                         Weapon,Potion,Armor,Spell αντιστοιχα, το ψαχνουν μεσα στο Inventory και αν το βρουν το αφαιρουν και επιστρεφουν 
                         εναν δεικτη σε αυτο. Αν δεν το βρουν επιστρεφουν NULL.
        
        <Equipment  >:  Συμβολιζει τα αντικειμενα που κραταει ο ηρωας.
                        -rightHand: Συμβολιζει το οπλο που κραταει ο ηρωας στο δεξι χερι του.
                        -lefttHand: Συμβολιζει το οπλο που κραταει ο ηρωας στο αριστερο χερι του.

                        -Αν ενας ήρωας κραταει οπλο και με τα δυο χερια, τοτε τα rightHand και lefttHand δειχνουν στο ιδιο οπλο.
                        -Armor: Συμβολιζει την armor που φοραει ο ηρωας.

                        ΣΗΜΑΝΤΙΚΕΣ ΠΑΡΑΤΗΡΗΣΕΙΣ:
                        -Η add(Armor& arm) προσθετει την arm στο Equipment. Αν πριν υπηρχε αλλη armor equipped o δεικτης που εδειχνε στην παλια
                         armor δειχνει αλλου πλεον.
                         Συνεπως ο χρηστης καλο θα ηταν να ελεγχει με τις getters συναρτησεις αν υπηρχε πριν κατι αλλο equipped, αλλιως υπαρχει κινδυνος για leaks
                         και ανεπιθυμητη συμπεριφορα/.

                        -Η add(Weapon& weap,string hand) δεχεται ως ορισμα ενα string. Ομοιως με τα παραπανω αν υπηρχε πριν αλλο οπλο, θα χαθεί.
                         Πρεπει να ειναι "Left" "Right" ή "Both"
                         "Left" -> ωστε το οπλο να μπει στο αριστερο χερι.
                         "Right" -> ωστε το οπλο να μπει στο δεξι χερι.
                         "Both" -> ωστε το οπλο να μπει και στα δυο χερια, αν ειναι TwoHandWeapon.

                         Σε οποιοδηποτε συνδιασμο χεριων και τυπου οπλων που δεν ειναι δεκτος, θα εμφανιζεται μηνυμα σφαλματος.
                         Για παράδειγμα αν δωθει η συμβολοσειρα "Both", αλλα το οπλο weap ειναι OneHandWeapon.


    ______________________________________________________________________________                  

    ______________________________________________________________________________
    ****************************|##ΑΡΧΕΙΟ Item.h|

        <Item>      :  Ειναι abstract κλαση και συμβολιζει ενα item. Τα items χωρίζονται σε Weapons,Armors,Potion.
                        Καθε item χαρακτηρίζεται απο ενα ονομα, ενα ελαχιστο level(minLevel) ωστε να μπορεσει να χρησιμοποιηθει
                        και απο μια τιμη αγορας. Τα παραπανω είναι private data mebers και οι τιμες τους καθοριζονται κατα την δημιουργια τους.
        
        <Weapon>    :   Ενα weapon είναι ένα(is-a κληρονομικοτητα) item. Χαρακτηρίζεται απο ένα attackDamage που καθορίζεται κατα 
                        την δημιουργια του weapon. Καθε weapon είναι OneHandWeapon ή TwoHandWeapon, για αυτο και η κλαση Weapon ειναι abstract κλαση 
                        και εχει δυο υποκλασεις τις: <OneHandWeapon> και <TwoHandWeapon>.

        
        <Armor>:        Mια armor ειναι ενα(is-a κληρονομικοτητα) item. Xαρακτηρίζεται απο μια τιμη resistance. Ειναι private και καθορίζεται κατα την
                        δημιουργια του αντικειμενου. Προσοχη, η armor ΔΕΝ ΕΙΝΑΙ ΑΣΠΙΔΑ αλλα ΠΑΝΟΠΛΙΑ. Συνεπως ενας παικτης μπορει να κραταει ΚΑI δυο οπλα
                        και να εχει ΚΑΙ armor.

        <Potion>:       Ενα ϕίλτρο (Potion) είναι ένα αντικείμενο το οποίο όταν το χρησιμοποιεί ένας ήρωας, αυξάνει κάποιο στατιστικό
                        του κατά κάποιο ποσό. Επειδη τα φιλτρα χωρίζοτναι και σε κατηγορίες, η κλαση Potion έχει 3 υποκλάσεις.
                        Την StrengthPotion, η οποιά αναφέρεται σε φίλτρο που αυξανει μόνο το strength, 
                        την DexterityPotion, η οποία αναφέρεται σε φίλτρο που αυξάνει μονο το dexterity
                        και στην AgilityPotion, η οποια αναφέρεται σε κλάση που αυξάνει μονο το Agility.
                        Ο λόγος που έγινε αυτη η κατηγοριοποιηση ειναι για λόγους επεκτασιμότητας, ώστε αργότερα να είναι δυνατή η προσθήκη
                        ιδιοτήτων στα φίλτρα ανάλογα με την κατηγορία τους.
                        Δεν επελεξα να είναι abstract κλαση, ωστε να δινεται η δυνατοτητα δημιουργιας φιλτρου που ανεβαζει παραπανω απο ένα στατιστικά.
    ______________________________________________________________________________


    ______________________________________________________________________________
    ****************************|##ΑΡΧΕΙΟ Living.h|

        <Living>:   Ενα ζωντανό ον (Living) αντιπροσωπεύει μια ζωντανή οντότητα του κόσμου του παιχνιδιού. ΄Εχει
                    ένα όνομα, κάποιο επίπεδο (level) καθώς και ένα ποσό ζωτικής ενέργειας (healthPower).

        <Hero>:     Ένας Hero ειναι (is-a κληρονομικοτητα) ένα Living. 
                    -Εχει μια μεταβλητη (magicPower) που είναι η μαγικη ενέργεια που εχει.
                     Η μαγικη ενεργεια αναλώνεται όταν χρησιμοποιούνται ξορκια.

                    -Εχει (strength) που υποδηλώνει το βασικό attackDamage του ηρωα χωρις την επιδραση των όπλων.

                    -Εχει μια μεταβλητη (experience) που δείχνει την εμπειρία του. Κατα σύμβαση 1000 experience αντιστοιχουν σε ένα level.
                     συνεπώς ενας ήρωας με 5000 experience για παράδειγμα θα ειναι το πολύ level 5.

                    Καθε ηρωας έχει σαν μελος της κλασης ενα Inventory που είναι η αποθηκη Weapons,Armors,spells,potions που μεταφερει.
                    Επισης εχει σαν μελος της κλασης ενα Equipment που δειχνει τα αντικειμενα που κραταει ο χρηστης.

                    ΣΗΜΑΝΤΙΚΕΣ ΠΑΡΑΤΗΡΗΣΕΙΣ:
                        -equipWeapon(string weaponName,string hand):
                        -levelUp(): Η level up εχει καποιους περιορισμους. levelUp γινεται ΜΟΝΟ οταν experience>=level*1000. Αυτο ωστε να μην καλειται αυθαιρετα
                                ακομα και όταν ο ηρωας δεν μπορει να ανεβει level. Οι λεπτομερειες βρισκονται σε σχολια στο αντιστοιχο κομματι του κωδικα.
         
        <Warrior>,<Sorcerer>,<Paladin>: Ειναι υποκλασεις του Hero. Ουσιαστικα καθε warrior,Sorcerer, Paladin ειναι ενας ηρωας, αλλα τα στατιστικα του
                ειναι εξειδικευμενα στον τυπο του ηρωα.
        
        <Monster>:  Είναι (is-a κληρονομικότητα) ένα Living.
                    Δεδομένα των αντικειμένων αυτών περιλαμβάνουν:
                    - περιορισμούς που έχουν εφαρμοστεί από spells
                    - αριθμό γύρων μάχης που απομένουν για τους συγκεκριμένους περιορισμούς
                    - γενικά χαρακτηριστικά του τέρατος, όπως τη ζημιά που προκαλεί σε κάθε επίθεση

                    Συνάρτηση receiveAttack:
                    Χρησιμοποιείται στη battle. Η battle την καλεί με όρισμα το ποσό ζημιάς που μπορεί να πάθει το τέρας από κάποιον ήρωα.
                    Η συνάρτηση αυτή αποφασίζει τυχαία αν το τέρας θα αποφύγει την επίθεση και αν δεν την αποφύγει, τότε αφαιρείται η ζημιά από τη ζωή του τέρατος.
                    Αν υπάρχει ενεργό LightingSpell, τότε η πιθανότητα αποφυγής επίθεσης είναι μειωμένη.

                    Οι συναρτήσεις enableDamageLimiter και reduceAAProbability χρησιμοποιούνται για τα IceSpell και LightingSpell, αντίστοιχα.
                    Λειτουργούν αποθηκεύοντας σε οριμένες μεταβλητές το ποσό του περιορισμού που εφαρμόζεται στο τέρας από το κάθε ξόρκι, καθώς και σε άλλες μεταβλητές τον
                    αριθμό των γύρων για τον οποίο ισχύουν οι συγκεκριμένοι περιορισμοί. Οι μεταβλητές αυτές επηρεάζουν τη λειτουργία συναρτήσεων όπως τη receiveAttack.
                    Στην περίπτωση του FireSpell, απλά καλείται η reduceHealth του τέρατος (που είναι Living και την έχει κληρονομήσει)


        <Dragon>, <Exosceleton>, <Spirit>: Είναι (is-a) τέρατα τα οποία έχουν αρχικοποιηθεί με ευνοημένα χαρακτηριστικά.



        
        get_random_monster: Συνάρτηση που αποφασίζει τυχαία και επιστρέφει κάποιο Monster/Dragon/Exosceleton/Spirit. Χρησιμοποιείται στη battle.


        Ο χρηστης αν θελει μπορει να επιλεξει να φτιαξει σκετο Ηero. Απλα τα στατιστικα του hero ειναι πιο ισορροπημενα.
       

    ______________________________________________________________________________
    ****************************|##ΑΡΧΕΙΟ Grid.h|

    <Grid>:     Το Grid περιγράφει τον κόσμο του παιχνιδιού. Είναι ένα πλέγμα απο τετραγωνάκια τα οποία έχουν συγκεκριμένες ιδιότητες.
                

                -Constructor του Grid: Παίρνει σαν όρισμα 4 strings, τα οποία είναι τα ονόματα των αρχειων με τα διαθέσιμα ονόματα απο 
                weapons, armors, spelss και potions( tα αρχεια για τα ονοματα πρεπει να βρισκονται στον ιδιο φακελο με την main).
                Tα στατιστικα αυτων των αντικειμένων αποφασίζονται με τυχαιότητα, αλλα οι τιμές αγοράς τους
                είναι ανάλογες των στατιστικών τους. 
                Συγκεκριμενα επιλέγεται τυχαία ένας αριθμός απο ένα διαστημα και ανάλογα με την τιμή του αριθμού αυτου αποφασίζεται η τιμή αγοράς
                του αντικειμενου και το minLevel του. Αυτή η διαδικασία γίνεται ώστε να εξασφαλιστει μια σωστή κατανομή μεταξυ κόστους και στατιστικών του αντικειμενου.

                Σε δεύτερη φάση ο Constructor δίνει στον χρήστη την επιλογη να επιλέξει ποσους ήρωες θέλει να έχει.
                Αν ο χρήστης δώσει αριθμο εκτος των ορίων [1,3], επιλέγεται αυτόματα ο αριθμός 1.
                Ύστερα, δίνει στον χρήστη την επιλογή να αποφασίσει τον τύπο του ήρωα που θέλει να φτιαξει και το ονομα του.    
                Τέλος φτιαχνει τον κόσμο του παιχνιδιού. Ο χρηστης αποφασιζει το μεγεθος του Grid και τον αριθμο των shops που θα εχει.
                Αν δωθουν όμως τιμές, έξω απο τα όρια που καθορίζονται, θα επιλεχθεί μια default τιμη απο τον constructor.
                Tα αντικείμενα του κάθε μαγαζιου επιλέγονται επισης με τυχαιότητα.

                -H κίνηση της ομαδας ηρωων, γίνεται μέσω της συνάρτησης move(string) και ανάλογα με το string που θα δωθεί(Up,Down,Left,Right).
                 Καθε φορα που η ομαδα ηρωων μετακινείται, αποφασίζεται με τυχαιότητα αν θα υπαρξη μαχη. Η πιθανοτητα μαχης ειναι 10% ανα μετακινηση.

                -Η αγορά αντικειμένων και spells γίνεται απο την συνάρτηση buy. Δέχεται για ορισματα 2 strings. To όνομα του ήρωα που θα αγοράσει
                κατι και το ονομα του item/spell που θα αγοράσει.
                

                -Η πώληση αντικειμένων/spells γίνεται απο την sell. Δέχεται για ορισματα 2 strings. To όνομα του ήρωα που θα πουλήσει
                κατι και το ονομα του item/spell που θα πουλήσει. Λοιπές λεπτομερειες βρισκονται στον αντιστοιχο κωδικα.

                -Απο το grid δινεται η δυνατοτητα προβολης του Inventory καποιου ηρωα.Αυτο γινεται απο την checkInventory(string) που δεχεται για string το όνομα
                 του ήρωα

                - Battle:
                Χρησιμοποιείται για τις μάχες μεταξύ των ηρώων και των τεράτων. Υπάρχουν δύο std::vector τα οποία κρατούν τους ζωντανούς ήρωες και τα ζωντανά
                τέρατα, αντίστοιχα. Μόνο όταν αδειάσει τουλάχιστον ένα από αυτά τα vectors τελειώνει η μάχη. Μέχρι να γίνει αυτό, θα παλεύουν ο front ήρωας και
                το front τέρας του κάθε vector. Όταν έρθει η σειρά του ήρωα, εκτυπώνονται οι διαθέσιμες ενέργειες που μπορεί να πράξει. Μεταξύ αυτών, είναι η
                attack και η castSpell, οι οποίες είναι συναρτήσεις τις οποίες καλεί η battle.
                Όταν είναι η σειρά των τεράτων, αποφασίζεται από το πρόγραμμα αν ο ήρωας θα δεχτεί επίθεση, το οποίο εξαρτάται από διάφορους παράγοντες, όπως το
                dexterity του ήρωα.

                - Attack και castSpell:
                Το πρόγραμμα εξετάζει αν το τέρας θα δεχτεί επίθεση ή αν την αποφύγει, καλώντας την bool receiveAttack του τέρατος.
                Στην περίπτωση της castSpell, ενδέχεται να κληθούν και άλλες συναρτήσεις από το τέρας, ώστε να εφαρμοστεί κάποιος περιορισμός στα χαρακτηριστικά του,
                όπως την πιθανότητα αποφυγής επίθεσης.

                 ΣΗΜΑΝΤΙΚΕΣ ΠΑΡΑΤΗΡΗΣΕΙΣ:
                 -equip: Ειναι συναρτηση με default ορισματα. Αν δωθει ορισμα στο string hand προσπαθει να κανει equip ενα weapon. Αν δεν δωθεί κανει equip armor.
                         Αν δωθει OneHandWeapon και ορισμα "Βoth", δηλαδη να παει και στα δυο χερια το οπλο, δεν θα βγει καποιο μηνυμα λαθους. Αντιθετως, γινεται ελεγχος
                         και το οπλο θα μπει μονο στο αριστερο χερι

                

    ______________________________________________________________________________
    ****************************|##ΑΡΧΕΙΟ Squares.h|

    Squares>:   Τα squares ειναι τα δομικα στοιχεια του grid.
                Aρχικα υπαρχει μια abstract κλαση η nullSquare. O λόγος που είναι abstract είναι ο πολυμορφισμος.


    <market>:   Το square market είναι ενα τετραγωνάκι πάνω στο οποίο υπάρχει ένα market. Κάθε market έχει 4 πινακες για την αποθήκευση
                weapons/armors/spells/potions. Η προσθηκη και η αφαιρεση αντικειμενων στην αγορα γίνεται μέσω των συναρτήσεων add/discardArmor/discardPotion/discardSpell/discardPotion.
                Μοναδική ιδιαιτερότητα του market είναι η συνάρτηση hasMarket() που ειναι επαναορισμενη στην κλάση. 
                Επιστρέφει true αν το τετραγωνακι εχει market.
                Ορίζεται επισης και στα common/nonAccessible τετραγωνακια, μονο που εκει επιστρεφει false.

    <common>:   Δεν υπαρχει καποια ιδιαιτερότητα.

    <nonAccessible>:  Δεν υπαρχει καποια ιδιαιτερότητα.



    ______________________________________________________________________________
    ****************************|##ΑΡΧΕΙΟ Spell.h|

    Περιέχει τα spells και τις υποκλάσεις τους. Κάθε spell έχει τα χαρακτηρικά του αποθηκευμένα σε διάφορες μεταβλητές, καθώς και
    συναρτήσεις-accessors για αυτά τα χαρακτηριστικά.

    Επιλέχτηκε η κατηγοριοποίηση των εξειδικευμένων spells σε υποκλάσεις ώστε να διευκολυνθεί τυχόν επεκτασιμότητα που μπορεί να γίνει στο μέλλον.


    ______________________________________________________________________________
    ****************************|##ΑΡΧΕΙΟ Randomness.h|

    Περιέχει αντικείμενα από τη <random> βιβλιοθήκη της C++11, όπως std::random_device και std::mt19937, τα οποία φυλάσσονται στο στατικό χώρο
    του προγράμματος, καθώς δε χρειάζεται να αρχικοποιηθούν περισσότερες από μία φορές.

    Προτιμήθηκε η χρήση αυτών των αντικείμενων από τη χρήση της rand, καθώς η rand θεωρείται προβλέψιμη και είναι της C και όχι της C++.
