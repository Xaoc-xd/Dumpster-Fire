#pragma once
#include "SDK.h"
#include "Util.h"
#include "TextFile.h"
#include <sstream>

class CKillSay : public IGameEventListener2
{
public:

	//void Run(CBaseEntity * pLocal, CUserCmd * pCommand);

	void InitKillSay();

	void FireGameEvent(IGameEvent * event);

	bool wasEventInitialized = false;

	std::string repeat(int n, const char* str)
	{
		std::ostringstream os;
		for (int i = 0; i < n; i++)
			os << str;
		return os.str();
	};

	TextFile killsayFile{};

};

namespace KillSay
{
	const std::vector<std::string> ncc =
	{
		"%s, you are a noob.", "%s, do you even lift?", "%s, you're a faggot.", "%s, stop cheating.",
		"%s: Mom, call the police - I've got headshoted again!", "Right into your face, %s.",
		"Into your face, pal.", "Keep crying, baby.", "Faggot. Noob.", "You are dead, not big surprise.",
		"Sit down nerd.", "Fuck you with a rake.", "Eat a man spear, you Jamaican manure salesman.",
		"Wallow in a river of cocks, you pathetic bitch.", "I will go to heaven and you will be in prison.",
		"Piss off, you poor, ignorant, mullet-wearing porch monkey.",
		"Your Mom says your turn-ons consist of butthole licking and scat porn.",
		"Shut up, you'll never be the man your mother is.",
		"It looks like your face caught on fire and someone tried to put it out with a fork.",
		"You're so ugly Hello Kitty said goodbye to you.",
		"Don't you love nature, despite what it did to you?"
	};

	const std::vector<std::string> niggerhook =
	{
		"%s, I would call you cancer, but cancer actually kills.",
		"I just owned %s.",
		"Mad? %s",
		"%s is mad because he died in a 10 year old dead source game :(",
		"%s I PRAY TO GOD A PACK OF WOLVES RAPES YOU IN THE DEAD OF WINTER AND FORCES YOU TO WALK HOME BAREFOOT!",
		"wow %s destroid p.s. ur utter shit",
		"ww %s SNAPPED u HARD (fkn shitter)",
		"%s did u kno if u take ld and replace L with B, u get BD, and thats u",
		"LMFAO nt %s retard ===--D~~ (cum)",
		"{{R@PeD}} :: btw you are shit %s",
		"%s is the reason why abortion is legal.",
		"%s hope ur ok with going on utube!!",
		"%s is a fuckin fagot LoLOLolLOLO!!!!",
		"%s Ll did u just buy dis game??!? ROFRRL",
		"LMAO %s u got SMASHD!! (and your dad fingers you)",
		"%s loL :D get bttr fgt (jk u cant)",
		"%s < SPRM (ESP UR DADZ LL) ~~~c====",
		"<--- BEATDOWN BRINGA (%s smashed u dickhead)",
		"%s!! rFL shat on -- ****nice play faggt****",
		"%s u suck dicks nigger go uninstall",
		"%s, wer u born yesterday??? ~~ ROFL shtty",
		"%s do you feel special? Please try suicide again... hopefully you will be successful this time.",
		"%s u did good.... for a fCKing~BADDIE...sht on",
		"%s lolURbd at an E-Z GAME (>^^)>",
		"%s go milk a cow you shitmongering cuntnugget",
		"%s = vrgin nrd~",
		"rekt nerd",
		"%s cheer up^ :) youre small dk isnt noticealbe under ur BaDnEsS",
		"==----**~~#NOOB DOWN#~~**----==",
		"%s NEWSFLASH NIGGA U AINT JEZUZ, NO  CAN BE JEZUZ LIKE H E WAS NIGGA U TIHNKIN U CAN?",
		"%s rack off you crazy little dingo!!! FFS????@!",
		"%s LL :-) LL u gt rPD idt :-) LL",
		"%s nt nigger (suck my cunt)",
		"%s **maybee** if u stoped jerkin it to anime u'd get a gf ^______^",
		"hey %s, its a gay virgn",
		"%s CRY SOME MORE - Team Fortress 2 Heavy Weapons Guy",
		"at least i have arms n legs (thats what it feels like playing vs %s)",
		"i laffed iRL b-cuz your so BAD %s *(<(<(OEWNED>)>)*",
		"%s you little fuckmunch of obliverating asswipe ",
		"%s GO BACK TO ASS-LAND YOU DICK-CODDLING PRINCE!",
		"**PROTIP** If you wanna frag people you have to hit them, %s.",
		"**PROTIP** Use the reticule in the middle of the screen to aim, %s.",
		"%s do you feel special? Please try suicide again... hopefully you will be successful this time.",
		"**PROTIP** Your crosshair generally assists you in aiming.",
		"rofl pubbers like %s are so bad its funny",
		"LOL WOW watchin %s play this game is like watching helen keller play tennis",
		"%s ahaha ur awful",
		"%s: i luv anime!!11",
		"%s lolumad",
		"calm down %s, ur bad, just accept it",
		"ROFL WOW BADDIES EVERYWHERE JUST LOOK AT %s",
		"qq  qq  qq q qq QQ %s",
		"%s poop on a noob autismal butfrustrated etc etc",
		"LMDOIUE %s (laf my dik off into ur ear)",
		"%s u hav week  live cuz u dying of stage  --own--",
		"%s your eyes leak cum when u cry and you swallow it when it runs down your cheeks, gay noob",
		"%s ur such a looser ur wife is paper bag",
		"%s u so asspissed rite now ur bluddy poo steam w/rage",
		"%s y dont u gbgayville ur dad is wait",
		"how dos it fel b autism %s?",
		"%s get the weiner out of your mouth, ShitFUckeDDDDD!~@#(",
		"%s ay are u Oscar teh grouch!?!? CUZ U LIV INA TRASHCAN!!!!!!!!!??",
		"%s lmfao ur an moron",
		"%s status: fucked [x] not fucked [ ] ",
		"%s = rekt",
		"%s don't hate me because I'm beautiful hate me because your boyfriend thinks so ~~~~",
		"%s hang urslef from a high cieling, u candy apple jabroni >:(",
		"I took ur mom out to a nice steak dinner, but rly it was my evil twin with ur mmm and I was at your house raping your father",
		"%s g rub your cock against a cheese grater you titcrapping twigfucker",
		"%s u only even touchin me cause my girl is screamin, im not gonna take a loss that aint legit -- i poop on u, im jus distracted",
		"%s Your mother swims out to meet troopships.",
		"%s your eyes leak cum when u cry and you swallow it when it runs down your cheeks, gay noob ",
		"%s shut the fuck up, you cock juggling thundercunt ",
		"%s ur butt's a testing ground for TD bombs - thermodicklear ",
		"%s everyone who loves you is wrong. ",
		"%s go climb a wall of dicks. ",
		"%s you're as dumb as a bag of doorknobs. Retarded doorknobs. ",
		"%s ur butt is like CAPITAL of the BUTT DUMBPSTER factory - u take the cum that no ordinary man could ",
		"Looks guys, a one man fag parade! ",
		"you must be a DIRTY, STINKING, GREESY HAIRED, CHEESY BREATH CUNT. ",
		"%s, you are what you eat, and you're a dick. ",
		"%s get the fuck out of my server you disgusting cum guzzling fuck puppet ",
		"%s your mother will die aborting my child. ",
		"%s go cry about it on ur facebook (except opps u have no friends nerd) ",
		"%s is a disgusting crusty cum drenched cum sock ",
		"%s i will puss in ur cumdumbtser ",
		"%s are you? retarted? ",
		"%s ur dog looks like a faggot ",
		"%s is a faggot",
		"%s your hair is a jizzmop and ur mouth is a shit depository and ur butts a FDA Approved Cum Processing Facility ",
		"i shld slap u in the tits %s",
		"%s yor dad calls u 'cc'  cumcaptin lawl ",
		"%s in gradeschol u wanted to b a butplumber when u grw up ",
		"horse status: fucked [x] not fucked [ ] ",
		"%s your facebok status = shitslaming fukfaced dickpipeing aspie ",
		"%s i called u a fukin nerd go blog abut it faggt ",
		"'i like to eat dady's steemy logs of poop  lunsh n diner while jackling of to naurto' - %s",
		"%s confratulasons u ar the new WORLD BUTTHURTED CHAMPEON ",
		"%s got first place in GETING OWND bY ME ",
		"rep up those wieners cos ur sure hungry for one ",
		"%s can u b anny more anal hurt rigt now???? ",
		"%s gb pussybaby land where u git ownd by dick ",
		"%s lol u troled so fukin hard u wan sum ice for the ASSBURN?? ",
		"%s u cry tears of blud and cum ur mom's penis out your angry butthole ",
		"I hav neer seen sum so pooper peeved %s ",
		"%s u ned to take chilpil and stop raping your ownasswit with husband ",
		"'omg i love sukn dicks and crying to link park' - %s",
		"%s ur butt is evaporating cum bcuz it is steaming wit anger ",
		"SUMBUDY is anally anguished ",
		"%s lol ur so bad u cant even find ur own dick ",
		"%s ur dad rapes u with peanut butter,shitty ",
		"%s whats that? oh, must be the sound of u getting creamed in the face by my grandfather baddy",
		"u were --- this close to being recognized by ur parents",
		"%s REALLY? what a fucking retraded cunt",
		"%s im gonna stick an egg in ur vaginal canal and punch it-",
		"%s youve just been HURT FEELINGS'd",
		"i bet u have a fetish FOR MEN LMAO",
		"%s ur just so madd all the time its  easy  own u",
		"'i like to drnikj sperm from my sperm bottle while waring my sperm necklace' - %s",
		"%s go drink ur moms bredst milk u fart commander",
		"%s wolth with a T-rex cock! what is the odds",
		"%s fail. really? U must b gay and a nigger",
		"rofl who the hell are these fools",
		"%s stfu nerd go grow balls",
		"%s are you serious you dumb bastard? you faggot as bitch cunt, i will piss in your mouth",
		"%s i feel like your dad after a morning fuck with your sister.. ",
		"sdlkjyfgretsyhesrerdxth sorry just fucking %s's mom on the keyboard",
		"I feel like Zeus after a morning fuck with Athena",
		"%s, i'm assuming that your a preteen in the u.s. with a cracking voice that has to hide his wet dream stained sheets",
		"i wish my girlfriend was as dirty as that shot, %s",
		"%s go back to grooming your neck-beard. By the way you've got homework due tomorrow.",
		"'I came all over my triple chins.' - %s",
		"top 10 faggots of 2007 - number 1 - %s",
		"%s you got knocked the fuck out",
		"%s buttdocktor evaluation: BUTTBLEED",
		"%s do u jus liev in ur own lil'' world u dumFUK??",
		"PERRRRRRRRRRRRRRRRRRRRRRRRRRRRKELE %s",
		"%s take a gun, put it in your mouth and pull the trigger",
		"%s, you are the smallest little shit I've ever seen, yet you are so amazingly funny.",
		"%s lol nigga hold on let me hit dis shot b u tell me how fly i am ------- aiight you can tell me now",
		"%s let me call my gf and get the name of her gynecologist, you seem to need one",
		"psycho!, take it deep meat bag!! i hope the place u live burns to the ground!",
		"%s just do the WORLD a Big fucking favour and just ROLE OVER AND FUCKING DIE",
		"HAHAHAH SO FUCKING BAD %s KILL YOURSELF LMFAO",
		"%s noone will care when you die dumb cunt",
		"%s = nigger",
		"%s ur so analmad n i dont even care",
		"%s deal w it gaylord",
		"%s enjoyn ur buttfrustration?",
		"%s u got wned",
		"%s ur just a petatic nerd",
		"%s colonrampage'd",
		"%s yu're tears feul my butownage",
		"%s get ur mom  lik teh tears of ur ballz, assmaster",
		"%s y r u so paind in the glute LOL",
		"%s i shit on niggers like u all da godbdamn time lmao",
		"cocks ahoy %s",
		"%s I RECOMMEND YOU TRY ANOTHER SPORT. LIKE KNITTING.",
		"%s YOU FUCKIN' FINGERBANGED YOUR COUSIN MAN. THAT'S A FUCKING FACT.",
		"%s shitty little crotch fruit",
		"%s i've never seen anyone so SPHINCTER SORE b lmao",
		"%s ur BUTTSTEAM is causing globul warming",
		"all my diks r laffing semen n ur nostrils %s",
		"%s ur gay boyfriends (u have like .  LOL) use chapstick for lube",
		"%s u seem  have analchafe, would u like a RAGE enema?",
		"%s you're mom was a man's anus WWROFL",
		"%s go jump in a lake ful of penises you portugeese masticator",
		"%s i would rite more about wning u but i dont speak AUTISM",
		"%s i will puss in ur mouth u stupid nigger",
		"'Y do so mny ppl make fun of my fetish for artichokes' - ur furaffinity blog",
		"%s got aborted like my ex-gf's baby",
		"raped with ease by an acne-ridden anime-watching virgin",
		"%s remember that one time u werent a gigantic fellatioqueen? me neither",
		"raped w/ ease %s",
		"they call me the nigger killer, %s ",
		"raped u faster than a turtle flys %s",
		"if i put penut butter on my balls u'd lick it off probably, shitty %s",
		"%s, my dog is smarter and smells better than you",
		"wow, welcome to shitlord-land :: populashion - %s ::",
		":::: APPROACHING FAGGOT CITY LIMITS :::: TURN BACK NOW ::::",
		"%s if i had the choice of fucking your face or having sex w/ jessica alba, i'd shit on your lips and make u eat it",
		"%s rofl im literally not even aiming right now",
		"%s oh are you angry? peeved? perturbed?",
		"%s i just dropped u like ehfk does wit his ubers ROLF",
		"%s difference between you and a dead kid? i would fuck the dead kids face bc he's attratctive LOL",
		"cum-captin reporting in, target acquired, 'i'm a fag' - %s",
		"%s go to an animal shelter an pick up a kitten, only way ur ever gettin pussy nerd virgin",
		"nothing in my life has prepared me for seeing a true idiot like %s play vidoegames",
		"%s i bet a  yr old cancer patient w/ terminel ballsack cancer has a bettewr life than u, homo",
		"maybe if u werent so shit u might be good lol fagnet",
		"%s lL get SHTTED on u bad turdkid",
		"%s prawned u fukin fatty fuck",
		"%s mushed u dorkfuck nerd",
		"%s you just got owned by a sponsored, professional gamer.",
		"lmfao ur an moran %s",
		"HEaD$hT Nb %s",
		"%s poned hard kid",
		"%s kid u dident survive",
		"%s ur under arrested for being shit",
		"%s ur trash kid",
		"%s STUNNING REALISATION: U r ReALlY fUKiN BAd aT ths game kid",
		"%s u have da right  be shit at games(o wait u already r lol)",
		"%s stop get stuck in door u fat fuck then i wont headsht u",
		"%s funny kid, u dont look like a fish so how come u gettin fucking BATTERED!!!!!",
		"%s you shud hold a funeral for my dick cos i buried it in ur MOM!!! lOL!!! c=======",
		"outskilled %s",
		"%s u make gettin wrecked look easy kid.. go back  ur mams tit",
		"%s $|_ShiTTeR**DeAd_ShiTTeR_|$-___-$|DA tRaNsFoRmAtIoN hAs beGuN|*",
		"%s <<SHITTER STATUS: WRCKeD!!!>>>",
		"%s CN aLL SHTTERS PLz bRD DA SHttErTrAIN, DESTnATIN: U JUST gT Fu|<In SmShED CHOO CHOO",
		"%s absOLUTEly WRECKED hahaha u fat mongal",
		"%s LOL u got fkne FOLDED u stuped fat dork",
		"%s FKN dork this a fps U Cant cast ur nerd spells!!! OWN ED!!!",
		"%s ur dads bummin ur faace u fat bent gay::GET MUNCHD",
		"%s #_roooooooooooooFL WREKCED U FUKN PIZZA FACE DORK",
		"%s is the number 1 attendee of university of bein a FUKING FAGET",
		"rofl did any see that dork get raped",
		"%s how i turn up difficulty in this shit serveR??",
		"%s LOL does this kid even have arms?? he so fuken SHIT!! hahahha",
		"%s poned u fat pussy get out ur mams basement",
		"%s hahaha go cry ure dads dick forever noob(pwned)",
		"%s? more like \"im a fuckin nigger\" lmao rekt",
		"%s I am sure you will do really well for the rest of this round, Cap'n Neckbeard of the SS Obesity.",
		"%s ur such a virgin you could make ur own brand of olive oil rofl~",
		"%s i bet the last time u felt a breast was in a kfc bucket",
		"you guys are failers",
		"%s CAN YOU PLEASE NOT BE SHIT",
		"%s you were just a turd out there",
		"%s can u stop sucking dicks so much ?",
		"'my ass bleeds' - %s",
		"%s just gor raped",
		"%s confirmed for Captain Buttmad of S.S.Rectally Devastated",
		"%s not a million poets in a million years could describe how much your ass hurts",
		"are u gay, %s?",
		"are u actually that gay, %s?",
		"%s 's butt integrity: 0%",
		"%s is a niggerjew roflmao",
		"%s how do u even sit down after that sphincter spearing lmao",
		"%s ur butt deserves to be in a museom for FAGS",
		"%s every time u see a male nurse you get an  eerection U HOMO",
		"'i wish i cud gurgle all the spoog and munch all the poop in the umiverce so i culd be cum n shit master' - %s",
		"%s only thing left u do in this world is to go all out and comitt BUTTSUICIDE",
		"d %s id u ever concider not being so fukin MAD?",
		"%s = bad.",
		"%s nice try, aspergers",
		"%s, face it cunt bugle, u have no friends, no skils, no life, no sexs, no nothing",
		"%s i shit on fools like u all da godbdamn time",
		"BUTTSHIT STATUS: ABSOLUTE SHIT[X] NOT ABSOLUTE SHIT[]",
		"%s get domed fatty",
		"virgin down",
		"wow %s that was fkin gay",
		"%s uffya$$ 1tap $$ sit fucking low kid rifk hhhhhh",
		"Player %s left the game (timed out)",
		"Player %s left the game (Disconnect by user.)",
		"Player %s left the game (VAC banned fom secure server)",
		"Player %s left the game (steam account globally banned)",
		"Player %s left the game (VAC banned fom secure server)",
		"%s is more toxic than the beaches at Fukushima",
		"%s, don't be upsetti, have some spaghetti",
		"%s, rest in spaghetti never forgetti",
		"%s, You're almost as salty as the semen dripping from your mum's mouth",
		"mad cuz bad",
		"%s, safest place for us to stand is in front of your gun",
		"%s, Options->How To Play",
		"How do you change your difficulty settings? My TF2 is stuck on easy",
		"%s, The only thing you carry is an extra chromosome.",
		"%s, You have the reaction time of a dead puppy.",
		"%s, idk if u know but it's mouse1 to shoot",
		"%s, is your monitor on ?",
		"%s, did you know that tf2 is free to uninstall?",
		"Oops, I must have chosen easy bots by accident",
		"server cvar 'sv_rekt' changed to 1.",
		"%s, You're the human equivalent of a participation award.",
		"%s, tf2 is too hard for you m8 maybe consider a game that requires less skill, like idk....solitaire",
		"WOW! %s imagine if your parents weren't siblings.",
		"Who are you sponsored by %s? Parkinson's?",
		"%s, you should have been a handjob",
		"%s, \\_/ < ----Cry here Africa needs water",
		"%s, You're the type of player to get 3rd place in a 1v1 match",
		"%s, Stephen Hawking has better hand - eye coordination than you.",
		"%s, You're an inspiration for birth control.",
		"%s, The guy who played CSGO with a wheel is better than you",
		"%s, I suggest turning your monitor on for improved gaming performance.",
		"%s, The only problem with your PC is that thing between your keyboard and your chair",
		"%s, I'm surprised that you were able hit the 'Install' button",
		"%s, I'd ask you to shoot yourself, but you'd probably still miss.",
		"%s, I'm pretty sure you've typed more sentences than landed shots.",
		"%s, If your face was a Counter Strike map, it would be de_formed.",
		"%s, You're as useful as Stephen Hawking's home gym",
		"%s, John Lennon is better at dodging bullets than you",
		"%s, You know this isn't turn based combat right? When they shoot at you feel free to shoot back.",
		"%s, If you were any more inbred you'd be a sandwich",
		"%s, Imagine going through a nine month pregnancy only to give birth to someone who can't push the fucking cart.",
		"%s, I would mentally duel with you, but I can see you're unarmed",
		"%s, I've never touched a cigarette. I feel a sense of regret for not doing it, because you gave me cancer anyway.",
		"%s, I'd call all of you cancer, but at LEAST cancer kills.",
		"%s, You know what man, blind gamers deserve a chance too.I support you.",
		"%s, You're worth less than a Steam trading card",
		"%s, You're the reason they need to put instructions on Bleach bottles",
		"%s, If you were on life support I would pull the plug to charge my phone.",
		"%s, I envy everyone that hasn't met you.",
		"%s, I'd like to see something from your point of view, but I can't seem to get my head that far up my ass.",
		"%s, You're so stupid that if you fell into a barrel of tits you'd come up sucking your thumb.",
		"%s, If you were any dumber we'd have to water you.",
		"%s, You should stop playing %class%, you seem pretty bad at it.",
		"%s, I don't know what your problem is, but ill bet its hard to pronounce.",
		"%s, Your birth certificate is an apology from the abortion clinic.",
		"Hey %s! Your mother was a snow blower!",
		"Hey %s, I'll plant a mango tree in your mom's ass and fuck your sister in its shade.",
		"%s, Your dad should have shot you on the wall.",
		"%s, Your face looks like someone tried to put out a forest fire with a screwdriver",
		"%s, The smartest thing that�s ever come from your mouth was my dick",
		"%s, Stop crying, you look so fucking fat when you cry.",
		"%s, Everyone who loves you is wrong.",
		"%s, Have you ever considered suing your mother for drinking while she was pregnant with you?",
		"%s, I wish you were retarded, because then you'd at least have an excuse.",
		"%s, You have the intelligence of a stillborn.",
		"%s, With a face like yours, I�d be careful who and what I make fun of",
		"%s, You think you're hot shit but you're really just cold diarrhea.",
		"%s, You're not worth the money it would have cost to abort you, and I can buy a coat hanger for $2.",
		"%s, It was a joke not a dick, don't take it so hard",
		"%s, You look like you smell like pee.",
		"%s, You're dumb as cow shit and only half as useful.",
		"%s, I would insult you but nature did a better job.",
		"%s, You're the reason the gene pool needs a lifeguard.",
		"%s, If I ate a bowl of alphabet soup, I could shit out a smarter sentence than any of yours.",
		"%s, 2090 called.You're dead and you wasted your time on earth.",
		"%s, you did a really good job tying your shoes this morning.We're all really proud of you and what you're able to accomplish.",
		"%s, You're so ugly, I couldn't pay a ten cent hooker five dollars to fuck ya.",
		"%s, Yo momma so fat that when she took a teleporter, she telefragged the entire server",
		"%s, Your moms so ugly, not even spy would disguise as her.",
		"%s, Two wrongs don't make a right, take your parents as an example.",
		"%s, Your family tree must be a cactus because everybody on it is a prick.",
		"%s, You're so ugly, when your mom dropped you off at school she got a fine for littering.",
		"%s, If laughter is the best medicine, your face must be curing the world.",
		"%s, You must have been born on a highway because that's where most accidents happen.",
		"%s, If ignorance is bliss, you must be the happiest person on earth.",
		"%s, You are proof that evolution CAN go in reverse."
	};

}

extern CKillSay gKillSay;

