enum {
	EFFECT_LIGHT,
	EFFECT_PARTICLE,
	EFFECT_ATTRACTOR
};

enum {
	LIGHT_ON,
	LIGHT_ON_NIGHT,
	LIGHT_FLICKER,
	LIGHT_FLICKER_NIGHT,
	LIGHT_FLASH1,
	LIGHT_FLASH1_NIGHT,
	LIGHT_FLASH2,
	LIGHT_FLASH2_NIGHT,
	LIGHT_FLASH3,
	LIGHT_FLASH3_NIGHT,
	LIGHT_RANDOM_FLICKER,
	LIGHT_RANDOM_FLICKER_NIGHT,
	LIGHT_SPECIAL,
	LIGHT_BRIDGE_FLASH1,
	LIGHT_BRIDGE_FLASH2,
};

enum {
	LIGHTFLAG_LOSCHECK = 1,
	// same order as CPointLights flags, must start at 2
	LIGHTFLAG_FOG_NORMAL = 2,	// can have light and fog
	LIGHTFLAG_FOG_ALWAYS = 4,	// fog only
	LIGHTFLAG_FOG = (LIGHTFLAG_FOG_NORMAL|LIGHTFLAG_FOG_ALWAYS)
};

class C2dEffect
{
public:
	struct Light {
		float dist;
		float range;	// of pointlight
		float size;
		float shadowRange;
		uint8 lightType;	// LIGHT_
		uint8 roadReflection;
		uint8 flareType;
		uint8 shadowIntensity;
		uint8 flags;		// LIGHTFLAG_
		RwTexture *corona;
		RwTexture *shadow;
	};
	struct Particle {
		int particleType;
		CVector dir;
		float scale;
	};
	struct Attractor {
		CVector dir;
		uint8 flags;
		uint8 probability;
	};

	CVector pos;
	CRGBA col;
	uint8 type;
	union {
		Light light;
		Particle particle;
		Attractor attractor;
	};

	C2dEffect(void) {}
	void Shutdown(void){
		if(type == 0){	// TODO: enum
			if(light.corona)
				RwTextureDestroy(light.corona);
			if(light.shadow)
				RwTextureDestroy(light.shadow);
		}
	}
};
static_assert(sizeof(C2dEffect) == 0x34, "C2dEffect: error");
