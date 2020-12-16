#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"

static uint8_t mac[6] = { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA };
static uint8_t ip[4] = { 192, 168, 2, 70 }; 

//static uint8_t gwip[4] = { 
//  0,0,0,0};
//static uint8_t dnsip[4] = { 
//  0,0,0,0 };
//static uint8_t dhcpsvrip[4] = { 
//  0,0,0,0 };
#define PREFIX "" 

// The compiler will replace any mention of "prefix" with the value remote at compile time.
WebServer webserver(PREFIX, 8083);//port 

//
#define pin9 9
#define pin8 8
#define pin6 6
#define pinA1 A1
#define pinA0 A0
#define pin3 3
#define pin2 2
#define pin1 1
#define pin0 0

int pwmRedTv=0;
int pwmBlueTv=0;
int pwmGreenTv=0;
int red = 0;  
int blue = 0;  
int green = 0;  
int orange = 0;
int purple= 0;
int sparkle = 0;

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool){
	/* encode base64      
	 * username: vaggelis  
	 * password: Smarthome   
	 * */
	 
	// Authenticate 
	if (server.checkCredentials("dmFnZ2VsaXM6U21hcnRob21l")) { 
		
		// Setup 
		if (type == WebServer::POST){
			bool repeat;
			char name[16], value[16];
			
			do{
				repeat = server.readPOSTparam(name, 16, value, 16);
				
				if (strcmp(name, "red") == 0){
					red = strtoul(value, NULL, 10);
				}
				
				if (strcmp(name, "green") == 0){
					green = strtoul(value, NULL, 10);
				}
				
				if (strcmp(name, "blue") == 0){
					blue = strtoul(value, NULL, 10);
				}
				
				if (strcmp(name, "orange") == 0){
					orange = strtoul(value, NULL, 10);
				}
				
				if (strcmp(name, "purple") == 0){
					purple = strtoul(value, NULL, 10);
				}
				
				if (strcmp(name, "sparkle") == 0){
					sparkle = strtoul(value, NULL, 10);
				}
				
				if (strcmp(name, "pwmRedTv") == 0){
					pwmRedTv = strtoul(value, NULL, 10);
				}
				
				if (strcmp(name, "pwmBlueTv") == 0){
					pwmBlueTv = strtoul(value, NULL, 10);
				}
				
				if (strcmp(name, "pwmGreenTv") == 0){
					pwmGreenTv = strtoul(value, NULL, 10);
				}
			
			} while (repeat);    
		
			server.httpSeeOther(PREFIX);

			return;
		}

		server.httpSuccess();

		// HTML page 
		if (type == WebServer::GET){

			P(message) = 
				"<!DOCTYPE html>"
				"<html>"
					"<head>"
					"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">"
					"<title> Smart Bedroom </title>"
					"<meta name='viewport' content='width=device-width, initial-scale=1'>"  
					//css phone friendly, fills the width of the device
					"<link rel='stylesheet' href=\"http://code.jquery.com/mobile/1.3.1/jquery.mobile-1.3.1.min.css\" />"
					"<script src=\"http://code.jquery.com/jquery-1.9.1.min.js\"></script>"
					"<script src=\"http://code.jquery.com/mobile/1.3.1/jquery.mobile-1.3.1.min.js\"></script>"
					"<script>"
						"$(document).ready(function(){ $('#red, #green, #blue, #orange, #purple, #sparkle, #pwmGreenTv, #pwmRedTv, #pwmBlueTv').slider; $('#red, #green, #blue, #orange, #purple, #sparkle, #pwmGreenTv, #pwmRedTv, #pwmBlueTv').bind( 'change', function(event, ui) { jQuery.ajaxSetup({timeout: 50}); /*not to DDoS the Arduino, you might have to change this to some threshold value that fits your setup*/ var id = $(this).attr('id'); var strength = $(this).val(); if (id == 'red') $.post('', { red: strength } ); if (id == 'green') $.post('', { green: strength } ); if (id == 'blue') $.post('', { blue: strength } );  if (id == 'orange') $.post('', { orange: strength } ); if (id == 'purple') $.post('', { purple: strength } ); if (id == 'sparkle') $.post('', { sparkle: strength } ); if (id == 'pwmGreenTv') $.post('', { pwmGreenTv: strength } ); if (id == 'pwmRedTv') $.post('', { pwmRedTv: strength } ); if (id == 'pwmBlueTv') $.post('', { pwmBlueTv: strength } ); });});"      "</script>"
					"</head>"
					
					"<body>"
						//"<div data-role='page'"
						"<div data-role=\"header\" data-position=\"inline\"> "
						"<center>Εξυπνο Σπιτι<center/> </div>"   
						"<div class=\"ui-body ui-body-e\">"        
						"<div data-role=\"fieldcontain\">"
                                                //theming values a-z
						"<div class='ui-bar-z'>"
						  "<center>"
							"<h1>  Φωτα   </h1>"
						  "<center/>" //try out collapsible
  						  "<label for=\"flip-3\">"
                                                    "<br> Φως Σαλονι <br>"
                                                  "</label>"
  						  "<select name=\"flip-3\" id=\"red\" data-role=\"slider\" data-theme=\"c\">"
    						    "<option value=\"0\">OFF</option>"
    						    "<option value=\"255\">ON</option>"
						  "</select> "

						// unnecessary code?
                                                "<center>"
                                                "<center/>"

						"<center>"
                                                  "<h1>"
                                                    "<br><br> Ρολα  "
                                                  "</h1> <br> "
                                                "<center/>"
                                                
						"<label for=\"flip-3\" <br> Μεγαλο Ρολο πανω <br> </label>"
						"<select name=\"flip-3\" id=\"blue\" data-role=\"slider\" data-theme=\"c\">"
						  "<option value=\"0\">OFF</option>"
						  "<option value=\"255\">ON</option>"
						"</select> "

						"<label for=\"flip-3\"> <br> Μεγαλο ρολο κατω <br></label>"
						"<select name=\"flip-3\" id=\"sparkle\" data-role=\"slider\" data-theme=\"c\">" 
						  "<option value=\"0\">OFF</option>"
						  "<option value=\"255\">ON</option>"
						"</select> "
						// unnecessary code?
                                                "</select> "
						"<center><center/>"

						"<label for=\"flip-3\"><br> Μικρο ρολο πανω  <br></label>"
						"<select name=\"flip-3\" id=\"purple\" data-role=\"slider\" data-theme=\"c\">"
						  "<option value=\"0\">OFF</option>"
						  "<option value=\"255\">ON</option>"
						"</select> "

						"<label for=\"flip-3\"><br> Μικρο ρολο κατω  <br></label>"
						"<select name=\"flip-3\" id=\"orange\" data-role=\"slider\" data-theme=\"c\">"
						  "<option value=\"0\">OFF</option>"
						  "<option value=\"255\">ON</option>"
						"</select> "

						"<label for=\"flip-3\"><br> Ρολο δωματιου πανω  <br></label>"
						"<select name=\"flip-3\" id=\"green\" data-role=\"slider\" data-theme=\"c\">"
						  "<option value=\"0\">OFF</option>"
						  "<option value=\"255\">ON</option>"
						"</select> "

						"<label for=\"flip-3\"><br> Ρολο δωματιου κατω  <br></label>"
						"<select name=\"flip-3\" id=\"pwmGreenTv\" data-role=\"slider\" data-theme=\"c\">"
						  "<option value=\"0\">OFF</option>"
						  "<option value=\"255\">ON</option>"
						"</select> "

						//"<label  for=\"slider\"><br> led strip  <br> </label>"
						//kodikas gia ledstrip                //      
						//"<input type=\"range\" name=\"slider\" id=\"pwmRedTv\" value=\"0\" min=\"0\" max=\"255\" data-highlight=\"true\" data-theme=\"a\" data-track-theme=\"b\"   />"
						//"<input type=\"range\" name=\"slider\" id=\"pwmBlueTv\" value=\"0\" min=\"0\" max=\"255\" data-highlight=\"true\" data-theme=\"a\" data-track-theme=\"b\"   />" 
								

						"</div>" 
						"<center>"
							"<img src=\"https://www.howtogeek.com/wp-content/uploads/2019/08/Many-Devices-HTG.jpg\">"
						"</center>" 
						"</div>" 
					"</body>" 
				"</html>";

			server.printP(message);
			//P(image)=
			//                                  "</div>"
			//                                  "<center><img src=\"http://oshwlogo.com/logos/oshw-logo-400-px.png\"></center>"      
			//                                  "</div>"
			//                                  "</body>"
			//                                  "</html>";
			//                 server.printP(image);    
		}
	} else {
		server.httpUnauthorized();
	}
}

void setup()
{
	pinMode(pin9, OUTPUT);
	pinMode(pin8, OUTPUT);
	pinMode(pin6, OUTPUT);
	pinMode(pinA1, OUTPUT);
	pinMode(pinA0, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin0, OUTPUT);
	pinMode(pin1, OUTPUT);

	analogReference(INTERNAL);	//temp calc

	Ethernet.begin(mac, ip);

	webserver.setDefaultCommand(&defaultCmd);
	webserver.begin();
}

void loop()
{
	webserver.processConnection();

	analogWrite(pin0,  purple);
	analogWrite(pin1,  orange);
	analogWrite(pin2,  sparkle);
	analogWrite(pin3,  pwmBlueTv);
	analogWrite(pinA0, green);
	analogWrite(pinA1, pwmGreenTv);
	analogWrite(pin6,  pwmRedTv);
	analogWrite(pin8,  blue);
	analogWrite(pin9,  red);
}
