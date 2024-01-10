#include <Wire.h>
#include "U8g2lib.h"

// '1337-logo', 3x47px
const unsigned char epd_bitmap_1337_logo [] PROGMEM = {
	0x00, 0x00, 0x00, 0xe6, 0xee, 0x00, 0x84, 0xa8, 0x00, 0xc4, 0x8c, 0x00, 0x84, 0x88, 0x00, 0xee, 
	0x8e, 0x00
};
// 'battery-icon', 3x47px
const unsigned char epd_bitmap_battery_icon [] PROGMEM = {
	0x00, 0x00, 0xfc, 0x3f, 0x06, 0x20, 0xf2, 0x2f, 0xf2, 0x2f, 0xf2, 0x2f, 0x06, 0x20, 0xfc, 0x3f, 
	0x00, 0x00
};
// 'bluetooth-icon', 3x47px
const unsigned char epd_bitmap_bluetooth_icon [] PROGMEM = {
	0x00, 0x08, 0x1a, 0x2c, 0x18, 0x2c, 0x1a, 0x08, 0x00
};
// 'page-structure', 3x47px
const unsigned char epd_bitmap_page_structure [] PROGMEM = {
	0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'racebot_logo', 3x47px
const unsigned char epd_bitmap_racebot_logo [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0xee, 0xee, 0x0e, 0x06, 0xaa, 0x22, 0xaa, 0x04, 0x04, 0xaa, 
	0x22, 0xaa, 0x04, 0x04, 0xe6, 0xe2, 0xa6, 0xe4, 0x04, 0xee, 0x22, 0xaa, 0xe4, 0x04, 0xaa, 0xee, 
	0xee, 0x04, 0x0e, 0xaa, 0xee, 0xee, 0x04, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00
	};
// 'scrollbar-handle', 3x47px
const unsigned char epd_bitmap_scrollbar_handle [] PROGMEM = {
	0x00, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x00
};
// 'scrollbar', 3x47px
const unsigned char epd_bitmap_scrollbar [] PROGMEM = {
	0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
	0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
	0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 448)
const int epd_bitmap_allArray_LEN = 7;
const unsigned char* epd_bitmap_allArray[7] = {
	epd_bitmap_1337_logo,
	epd_bitmap_battery_icon,
	epd_bitmap_bluetooth_icon,
	epd_bitmap_page_structure,
	epd_bitmap_racebot_logo,
	epd_bitmap_scrollbar,
	epd_bitmap_scrollbar_handle
};




const int MENU_ITEMS = 4;          // Items to be written on screen [8]
const int MENU_ITEMS_LENGTH = 10;   // maximum characters for the item name [10], max 20 characters allowed

char menu_items [MENU_ITEMS] [MENU_ITEMS_LENGTH] = {   // array with main menu item names
{ "Dashboard" }, 
{ "Settings" }, 
{ "GPIO pins" },
{ "About" }
};


const int SETTINGS_ITEMS = 5;          // Items to be written on screen [8]
const int SETTINGS_ITEMS_LENGTH = 10;   // maximum characters for the item name [10], max 20 characters allowed

char settings_items [SETTINGS_ITEMS] [SETTINGS_ITEMS_LENGTH] = {  // array with settings item names
{ "Motors" }, 
{ "Lights" },
{ "Buzzer" },  
{ "Battery" }, 
{ "Oled" }
};


U8G2_SSD1306_128X64_NONAME_F_HW_I2C menuList(U8G2_R0);

void setup()
{
  menuList.setColorIndex(1);  // set the color to white
  menuList.begin();
  menuList.setBitmapMode(1);   
  displayMenu();                                                          //Create object for oled panel
}

void loop() {  
  
}

void displayMenu()
{
  menuList.clearBuffer();  // clear buffer for storing display content in RAM

	
  displayStaticPage();
  displayMenuItems(0);

  menuList.sendBuffer(); // send buffer from RAM to display controller
}

void displayStaticPage()
{
  menuList.drawXBMP(107, 0, 7, 9, epd_bitmap_bluetooth_icon);
	menuList.drawXBMP(114, 0, 15, 9, epd_bitmap_battery_icon);
  menuList.drawXBMP(112, 58, 17, 6, epd_bitmap_1337_logo);
	menuList.drawXBMP(45, 0, 37, 9, epd_bitmap_racebot_logo);
	menuList.drawXBMP(125, 10, 3, 47, epd_bitmap_scrollbar);
	menuList.drawXBMP(124, 10, 4, 13, epd_bitmap_scrollbar_handle);

  menuList.drawHLine(0, 9, 128);
}

void displayMenuItems(uint8_t i)
{
  menuList.setFont(u8g2_font_Pixellari_tf);
  menuList.drawStr(10, 25, menu_items[i%MENU_ITEMS]);      
  menuList.drawFrame(1,25+2,123,15+2+3);
  menuList.drawStr(10, 25+15+2, menu_items[(i+1)%MENU_ITEMS]);      
  menuList.drawStr(10, 25+15+15+2+4, menu_items[(i+2)%MENU_ITEMS]);   
}

void displaySettingsItems(uint8_t i)
{
  menuList.setFont(u8g2_font_Pixellari_tf);
  menuList.drawStr(10, 25, settings_items[i%SETTINGS_ITEMS]);      
  menuList.drawFrame(1,25+2,123,15+2+3);
  menuList.drawStr(10, 25+15+2, settings_items[(i+1)%SETTINGS_ITEMS]);      
  menuList.drawStr(10, 25+15+15+2+4, settings_items[(i+2)%SETTINGS_ITEMS]);   
}