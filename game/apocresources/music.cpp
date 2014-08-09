
#include "music.h"

long Music::starts[] = { 0, 8467200, 19580400, 35897400, 40131000, 46569600, 57947400, 72147600, 84142800, 92610000, 104076000, 107780400, 118540800, 130712400, 142090200, 154085400, 165904200, 176664600, 187248600, 196686000, 207270000, 218559600, 231436800, 234082800, 237169800, 239815800, 242461800, 245107800, 247842000, 250488000, 263365200, 275801400, 287796600, 298821600, 304819200 };
long Music::lengths[] = { 8202600, 19404000, 35897400, 40131000, 46569600, 57859200, 72147600, 84054600, 92610000, 103987800, 107780400, 118452600, 130536000, 142090200, 153997200, 165816000, 176488200, 187072200, 196686000, 207093600, 218383200, 231348600, 234082800, 237169800, 239815800, 242461800, 245107800, 247842000, 250488000, 263188800, 275713200, 287708400, 298821600, 304731000, 311434200 };

Music::Music( int Track )
{
	ALLEGRO_FILE* f = DATA->load_file( "MUSIC", "rb" );
	sounddata = new Memory( lengths[Track] );
	al_fseek( f, starts[Track], ALLEGRO_SEEK_SET );
	al_fread( f, sounddata->GetData(), lengths[Track] );
	al_fclose( f );

	soundsample = al_create_sample( sounddata->GetData(), sounddata->GetSize(), 22050, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2, false );
}

Music::~Music()
{
	al_destroy_sample( soundsample );
	delete sounddata;
}

void Music::Play()
{
	al_play_sample( soundsample, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, 0 );
}

void Music::Stop()
{
	al_destroy_sample( soundsample );
	soundsample = al_create_sample( sounddata->GetData(), sounddata->GetSize(), 22050, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2, false );
}
