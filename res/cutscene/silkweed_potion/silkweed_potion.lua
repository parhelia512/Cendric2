-- lua script for cutscene silkweed_potion
mapid = "res/map/elderhome/elderhome.tmx"
worldx = 580
worldy = 440
steps = {
	{
		texts = {
			{str="Elder:HereDrink", 	time=4},
			{str="Elder:ItWillReveal", time=5},
			{str="Elder:TakeWater", time=5}

		},
		images = {
			{path="1_i_1.png", vel=0,  angle=0},
			{path="1_i_2.png", vel=5, angle=90},
			{path="1_i_3.png", vel=8, angle=90},
		}
	},
	{
		texts = {
			{str="Cendric:LetsDrink", time=6}

		},
		images = {
			{path="1_i_1.png", vel=0,  angle=0},
			{path="1_i_2.png", vel=10, angle=270},
			{path="2_i_3.png", vel=15, angle=270},
		}
	},
	{
		texts = {
			{str="Cendric:Cough", time=2},
			{str="Cendric:Aah",   time=2},

		},
		images = {
			{path="3_i_1.png", vel=0,   angle=0},
			{path="3_i_2.png", vel=120, angle=180}
		}
	},
	{
		texts = {
			{str="Crash", time=4}

		},
		images = {
			{path="4_i_1.png", vel=0,  angle=0},
			{path="4_i_2.png", vel=30, angle=315},
			{path="4_i_3.png", vel=30, angle=45}
		}
	},
	{
		texts = {
			{str="Cendric:ItBurns",        time=3},
			{str="Cendric:WhatsHappening", time=4}

		},
		images = {
			{path="5_i_1.png", vel=0,   angle=0},
			{path="5_i_2.png", vel=50,  angle=180},
			{path="5_i_3.png", vel=100, angle=180}
		}
	},
	{
		texts = {
			{str="Cendric:IFeelSomething", time=3},
			{str="Cendric:SoCold",         time=2}

		},
		images = {
			{path="6_i_1.png", vel=0, angle=0}
		}
	},
	{
		texts = {
			{str="Cendric:AmI",   time=3},
			{str="Cendric:AMage", time=7}

		},
		images = {
			{path="6_i_1.png", vel=0,  angle=0},
			{path="6_i_2.png", vel=10, angle=0},
			{path="6_i_3.png", vel=20, angle=0},
			{path="6_i_4.png", vel=40, angle=10},
			{path="6_i_5.png", vel=40, angle=350}
		}
	},
	{	
		texts = {
			{str="Cendric:TheVisionOver", 	time=3},
			{str="Cendric:TheWaterFrozen", time=4},
			{str="Cendric:IDidThat", 		time=4},
			{str="Cendric:WhatsThis", 		time=3}

		},
		images = {
			{path="7_i_1.png", vel=0, angle=0},
			{path="7_i_2.png", vel=10, angle=0},
			{path="5_i_3.png", vel=150, angle=0}
		}
	},
	{	
		texts = {
			{str="Cendric:AMark", 			 time=3},
			{str="Cendric:WasntHereBefore", time=4}

		},
		images = {
			{path="8_i_1.png", vel=0, angle=0},
			{path="8_i_2.png", vel=10, angle=0}
		}
	}
}

musicpath = "res/cutscene/silkweed_potion/silkweed_potion.ogg"
