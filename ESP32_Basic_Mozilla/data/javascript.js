
/***********************************************************************
*! \fn          int16_t create_fb(char *dataPtr, byte *fb)
*  \brief       reset the Framebuffer
*  \param       dataPtr String to scroll across
*  \param       fb Pointer to the frame buffer array
*  \exception   none
*  \return      length of frame buffer
***********************************************************************/             
function build_menu(ul, menu){

    var get_menu_length = Object.keys(menu).length
    console.log(get_menu_length);

    for (var i in menu.mainmenu) {
        x = menu.mainmenu[i].name;
        //var li = ('<li><a href="">' + menu.mainmenu[i].name + '</a></li>'); 
        console.log(li);
    }
   

}


/***********************************************************************
*! \fn          int16_t create_fb(char *dataPtr, byte *fb)
*  \brief       reset the Framebuffer
*  \param       dataPtr String to scroll across
*  \param       fb Pointer to the frame buffer array
*  \exception   none
*  \return      length of frame buffer
***********************************************************************/             
function ShowDateAndTime(){

    var today = new Date();
    var month = today.getMonth();
    var day = today.getDay();
    var year = today.getFullYear();
    var hour = today.getHours();
    var minute = today.getMinutes();
    var seconds = today.getSeconds();
    const options_date = {year: 'numeric', month: 'long', day: 'numeric' };
		const options_weekday = { weekday: 'long' };
    //document.getElementById('id_alarm_browser_width').innerHTML = 'Browser Height = ' + window.innerHeight;
    //document.getElementById('id_alarm_browser_heigth').innerHTML = 'Browser Width = ' + window.innerWidth;
    document.getElementById('id_header_date').innerHTML = today.toLocaleDateString('de-DE', options_date);
    document.getElementById('id_header_day_and_time').innerHTML = today.toLocaleDateString('de-DE', options_weekday) +" " + leadingzero(hour) + ':' + leadingzero(minute) + ":" + leadingzero(seconds);
    document.getElementById('id_header_user').innerHTML = "none";
    
    
    /*if(window.innerWidth < 1000)
        sidebar_handle("id_alarm_sidebar", 0);
    else
         sidebar_handle("id_alarm_sidebar", 1);
    
    if(window.innerWidth < 700)
        sidebar_handle("id_navigation_sidebar", 0);
    else
         sidebar_handle("id_navigation_sidebar", 1);*/
		//window.status = "test";
}

/***********************************************************************
*! \fn          function leadingzero (number)
*  \brief       set leading zero to numer
*  \param       number
*  \exception   none
*  \return      number with leading
 ***********************************************************************/             
function leadingzero (number) {
    return (number < 10) ? '0' + number : number;
}

/***********************************************************************
*! \fn          function sidebar_handle(clicked_id, state)
*  \brief       control the sidbars
*  \param       clicked_id - id of sender
*  \param       state - 0 close, 1 open, 2 toggle
*  \exception   none
*  \return      number with leading
 ***********************************************************************/ 
function sidebar_handle(clicked_id, state){
	 
	  var NavigationBar_ID = "navigation_sidebar";
	  var AlarmingBar_ID = "alarm_sidebar";
	 
	  if(clicked_id.indexOf(NavigationBar_ID) >= 0 ){
	     
		    switch(state){
			      case 0: {
				        document.getElementById("id_navigation_sidebar").style.width = "20px";
				        document.getElementById("id_main_content").style.marginLeft = "20px";
  				  break;
	  		    }
		  	    case 1: {
			  	      document.getElementById("id_navigation_sidebar").style.width = "200px";
				        document.getElementById("id_main_content").style.marginLeft = "200px";
				        break;
  			    }
	  		    case 2:{
		  		      if(document.getElementById("id_navigation_sidebar").clientWidth > 20){
			   		        document.getElementById("id_navigation_sidebar").style.width = "20px";
				            document.getElementById("id_main_content").style.marginLeft = "20px";
				        }
				        else{
					          document.getElementById("id_navigation_sidebar").style.width = "200px";
				            document.getElementById("id_main_content").style.marginLeft = "200px";
				        }
				       break;
  			    }
	  		    default: {
		  	        break;
			      }
		    }		
	  }
    
    //handle Alarm clicks
    
    if(clicked_id.indexOf(AlarmingBar_ID) >= 0 ){
	    
		    switch(state){
			      case 0: {
				        //document.getElementById("id_alarm_sidebar").style.width = "20px";

  				  break;
	  		    }
		  	    case 1: {
			  	      //document.getElementById("id_alarm_sidebar").style.width = "200px";

				        break;
			      }
  			    case 2:{
	  			      /*if(document.getElementById("id_alarm_sidebar").clientWidth > 20){
		  			        document.getElementById("id_alarm_sidebar").style.width = "20px";
			  	      }
				        else{
					          document.getElementById("id_alarm_sidebar").style.width = "200px";
				        }
  				     break;*/
	  		    }
		  	    default: {
			          break;
			      }
		    }	
	  }
}

function openMenu() {
			document.getElementById("id_navigation_sidebar").style.width = "200px";
			document.getElementById("id_main_content").style.marginLeft = "200px"
      document.getElementById("id_menu_btn_open").style.display = "none"
		}
function closeMenu() {
			document.getElementById("id_navigation_sidebar").style.width = "20px";
			document.getElementById("id_main_content").style.marginLeft = "20px"
      document.getElementById("id_menu_btn_open").style.display = "block"
}


