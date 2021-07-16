#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 col;

uniform mat4 projection;

out vec4 v_col;

void main()
{
	gl_Position = projection * vec4(position.x, position.y, position.z, 1.0);
	v_col = col;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec4 v_col;

void main()
{
	color = v_col;
}