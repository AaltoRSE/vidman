uniform sampler2D texture;

in vec2 varyingTextureCoordinate;

varying out vec4 fragColor;

void main(void)
{
    fragColor = texture2D(texture, varyingTextureCoordinate);
}
