#version 130

//con esta variable accedemos al sampler que es quien agarrara pixel por pixel
//hacemos uno por textura, el impresionante poder programacional de los LMADs a la vista
uniform sampler2D text1;
uniform sampler2D text2;
uniform sampler2D text3;

//la intensidad viene del vertex shader como out
varying vec3 Normal;
varying vec3 vecLuz;
in vec4 Color;
vec3 color_temp1;
vec3 color_temp2;
vec3 color_temp3;

void main() {
	
	//obtenemos la intensidad, si utilizamos la posicion de la luz solamente
	//sera direccional, si la restamos del vertice sera puntual
	float intensidad = max(dot(Normal, -vecLuz),0);

	//luz ambiental es el factor minimo de iluminacion del pixel
	vec3 ambiente = vec3(0.1,0.1,0.1);
	//obtenemos el pixel con el sampler de la textura 1
	color_temp1 = vec3(texture2D( text1, gl_TexCoord[0].st));
	//obtenemos el pixel con el sampler de la textura 2
	color_temp2 = vec3(texture2D( text2, gl_TexCoord[0].st));
	//obtenemos el pixel con el sampler de la textura 3
	color_temp3 = vec3(texture2D( text3, gl_TexCoord[0].st));

	//suma las tres texturas para dar el multitextura
	vec3 color_final = color_temp1 * Color.r + color_temp2 * Color.g + color_temp3 * Color.b;		
	//je suis incroyable!
	
	//gl_FragColor = vec4(color_final*intensidad + color_final*ambiente,1);	
	
	gl_FragColor = vec4(color_final + color_final*ambiente,1);
    vec4 Col =vec4(color_final + color_final*ambiente,1); 
    vec4 Fcolor = mix(gl_Fog.color,Col, gl_Fog.density) ; 
    gl_FragColor = Fcolor; 	
	
	//gl_FragColor = vec4(color_final/**intensidad*/ + color_final*ambiente,1);
    //vec4 Col =vec4(color_final/**intensidad*/ + color_final*ambiente,1); 
    //vec4 Fcolor = mix(gl_Fog.color,Col, gl_Fog.density) ; 
    //gl_FragColor = Fcolor; */ 		
	
	
}
