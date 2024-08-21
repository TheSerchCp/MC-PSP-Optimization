#include <Minecraft/Mobs/Enderman.h>
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.14159f
#define DEG_TO_RAD (PI / 180.0f)
#define PIXEL 1.0f / 16.0f
#define GRAVITY -6.8f
#define JUMPVELOCITY 4.6f
#include <Minecraft/CraftWorld2.h>


Enderman::Enderman(Vector3 position1, int number1) : LameMob(position1, number1)
{
    //Definir el vector para las piernas
        legs = Vector3(0,PIXEL*-6,0);

    //Definir el vector para ambas piernas
      SetCollideBox(Vector3(PIXEL*4,PIXEL*18,PIXEL*4),Vector3(PIXEL*4,PIXEL*12,PIXEL*4));
    bBox = BoundingBox(Vector3(0,0,0),Vector3(0,0,0));

    rHandAngle = PI / 2 + PI;
    lHandAngle = PI / 2 + PI;

    animHandAngle = 0.0f;
    animHandAngleT = 0.0f;

    animLegAngle = 0.0f;
    animLegAngleT = 0.0f;

    rLegAngle = PI;
    lLegAngle = PI;

    SPD = 1.1f;
    HP = 28.0f;

    friendly = false;

    sunTimer = (rand() % 14)/10.0f;

    freezedTimerMax = 60.0f;

    UpdateBBox();

    mainTexture = TextureHelper::Instance()->GetTexture(TextureHelper::endermanTexture);

}

Enderman::~Enderman()
{

}

void Enderman::BoxCollision()
{
    for(int x = 0; x < world->mEndermans.size(); x++)
    {
        Enderman *TestEnderman = world->mEndermans[x];
        if(TestEnderman->number != number && (TestEnderman->position.x != position.x || TestEnderman->position.z != position.z || TestEnderman->position.y != position.y))
        {
            if(TestEnderman->bBox.intersect(bBox))
            {
                float angle1 = ATAN2_fast(position.x-TestEnderman->position.x,position.z-TestEnderman->position.z); // super secret function

                TryToMove(Vector3(sinf(angle1),0.0f,cosf(angle1)),SPD*0.05f);
            }
        }
    }
}


void Enderman::TakeDamage(float damage, float power, float dt)
{
    float AP = 2.0f;
    

    HP -= damage*(1.0f-(AP/25.0f));

    kicked = true;
    damaged = true;
    damagedTimer = power*0.6f+0.15;
    velocity.y = (power+0.15f) * JUMPVELOCITY;
    walkingOnGround = false;

    position += velocity * dt;
    playHurtSound = true;

    lastKickType = 1; //by player
}

void Enderman::TakeDamageFromPointExplosion(float damage, float power, float dt, Vector3 point)
{
    explosionPos = point;

    float AP = 2.0f;
    //No cuenta con armadura
    // AP = 2.0f + world->FetchArmorPoints(bootsId, leggingsId, chestplateId, helmetId);

    HP -= damage*(1.0f-(AP/25.0f));

    kicked = true;
    damaged = true;
    damagedTimer = power*0.6f+0.15;
    velocity.y = (power+0.25f) * JUMPVELOCITY;
    walkingOnGround = false;

    position += velocity * dt;
    playHurtSound = true;

    lastKickType = 2; //by explosion
}

void Enderman::Update(CraftWorld *myWorld, Vector3 playerPos, float dt)
{
    world = myWorld;
    BoundingBox playerHitBox = BoundingBox(Vector3(playerPos.x - 0.73f,playerPos.y - 1.65f,playerPos.z - 0.73f),
                                           Vector3(playerPos.x + 0.73f,playerPos.y + 0.2f,playerPos.z + 0.73f));

    distanceToPlayer = DistanceToPlayer();
    fastDistanceToPlayer = FastDistanceToPlayer();

    if(killed == true)
    {
        if(deathAngle < PI/2)
        {
            deathAngle += (PI/2)*dt*1.7+((PI/2-deathAngle)/24);
        }

        if(deathAngle > PI/2)
        {
            deathAngle = PI/2;
        }

        deathTimer -= dt;
    }

    if(toDestroy == false)
    {
        relPlayerPos = playerPos;
        if(dt < 0.1f)
        {
            sunTimer += dt;
            if(sunTimer > 1.5f)
            {
                if((world->worldDayTime > 6 && world->worldDayTime < 21 && world->GetShadowLevel(position.x,position.y-0.2f,position.z) == 0) && world->worldWeather->GetWeatherType() == 0)//clear weather, sun, enderman under clear sky
                {
                    HP -= 2.0f;
                    damaged = true;
                    damagedTimer = 0.9f;

                    playHurtSound = true;
                }
                sunTimer = 0.0f;
            }
        }
        if(fastDistanceToPlayer < world->mainOptions.horizontalViewDistance*14+5)
        {
            freezedTimer = 0.0f;
            if(HP <= 0.0f && killed == false)
            {
                killed = true;
                playDieSound = true;
                SetCollideBox(Vector3(PIXEL*4,PIXEL*5,PIXEL*4),Vector3(PIXEL*4,PIXEL*12,PIXEL*4));
                return;
            }

            UpdateBBox();


            /// TIMERS --- *
            if(dt < 0.1f)
            {
                sayTimer -= dt;
                if(sayTimer < 0.0f)
                {
                    playSaySound = true;
                    sayTimer = 10.0f + (rand() % 160)/10.0f;
                }

                jumpTimer += dt;
                if(jumpTimer > 0.2f)
                {
                    jumpReady = true;
                    jumpTimer = 0.0f;
                }

                if(damaged == true)
                {
                    if(damagedTimer > 0.0f)
                    {
                        damagedTimer -= dt;
                    }
                    else
                    {
                        damagedTimer = 0.0f;
                        damaged = false;
                    }
                }

                if(distanceToPlayer <= 2.42f)
                {
                    if(nearToPlayer == false)
                    {
                        kickTimer = 0.95f;
                    }
                    nearToPlayer = true;
                }
                else
                {
                    nearToPlayer = false;
                }

                if(nearToPlayer == true)
                {
                    kickTimer += dt;
                    if(kickTimer >= 1.0f)
                    {
                        Vector3 checkPos = (playerPos-position)*0.5f;
                        Vector3 checkPos2 = (playerPos-position)*0.75f;
                        Vector3 checkPos3 = (playerPos-position)*0.25f;
                        if(world->BlockSolid(position.x+checkPos.x,position.y+checkPos.y,position.z+checkPos.z) == false && world->BlockSolid(position.x+checkPos2.x,position.y+checkPos2.y,position.z+checkPos2.z) == false && world->BlockSolid(position.x+checkPos3.x,position.y+checkPos3.y,position.z+checkPos3.z) == false)
                        {
                            if(world->HP > 0)
                            {
                                world->kickedStart = true;
                                world->kickedAngle = ATAN2_fast(position.x-myWorld->playerPos.x,position.z-myWorld->playerPos.z);
                                world->kickedBy = 1;
                                world->kickedDamage = 3;
                            }

                            kickTimer = 0.0f;
                        }
                    }
                }

                /// * --- END



                /// BECOME ANGRY --- *
                if(killed == false)
                {
                    if(fastDistanceToPlayer < 15 && world->HP > 0) // it sees you
                    {
                        haunting = false;
                        hauntingTimer = 0.0f;
                        hauntingTimerMax = 0.0f;
                        hauntingPos = Vector3(0,0,0);
                        hauntingAngle = 0.0f;

                        if(distanceToPlayer > 1.3f)
                        {
                            angred = true;
                        }
                        else
                        {
                            moving = false;
                        }
                    }
                    else // it doesn't see the player
                    {
                        headAngleZ = 0.0f;
                        headAngleY = 0.0f;
                        moving = false;
                        angred = false;
                        haunting = true;

                        if(hauntingTimerMax == 0.0f)
                        {
                            hauntingTimerMax = 5.0f + rand() % 6;
                        }

                        if(hauntingTimer < hauntingTimerMax)
                        {
                            hauntingTimer += dt;
                        }
                        if(hauntingTimer >= hauntingTimerMax)
                        {
                            hauntingTimer = 0.0f;
                            if(rand()%100 < 80) // walk to some point nearby
                            {

                                hauntingTimerMax = 4.0f + (rand() % 27)/5.0f;
                                if(rand() % 5 == 0)
                                {
                                    hauntingTimerMax = 1.0f+(rand() % 20)/10.0f;
                                }

                                hauntingPos.x = position.x - 6 + (rand() % 120)/10.0f;
                                hauntingPos.z = position.z - 6 + (rand() % 120)/10.0f;

                                if(hauntingPos.x > world->WORLD_SIZE-3)
                                {
                                    hauntingPos.x = world->WORLD_SIZE-3;
                                }
                                if(hauntingPos.x < 2)
                                {
                                    hauntingPos.x = 2;
                                }

                                if(hauntingPos.z > world->WORLD_SIZE-3)
                                {
                                    hauntingPos.z = world->WORLD_SIZE-3;
                                }
                                if(hauntingPos.z < 2)
                                {
                                    hauntingPos.z = 2;
                                }

                                hauntingAngle = ATAN2_fast(position.x-hauntingPos.x,position.z-hauntingPos.z)+PI;
                            }
                            else // just rotate about its own position
                            {
                                hauntingTimerMax = 2.0f+(rand()%13)/5.0f;
                                hauntingAngle = (rand() % 360)/180.0f*PI;

                                hauntingPos = Vector3(-1,-1,-1);
                            }
                        }
                    }
                    /// * --- END


                    /// SWIMING --- Implementar daño en el agua* 
                    if(world->PlayerInWater(position) == true && jumpReady == true && killed == false)
                    {
                       
                    }
                    /// * --- END



                    /// MOVING WHEN ANGRY ---- *
                    if(angred == true && kicked == false)
                    {
                        checkCollisionTimer += dt;
                        if(checkCollisionTimer >= 0.1f)
                        {
                            BoxCollision();
                            checkCollisionTimer = 0.0f;
                        }

                        float playerAngle = ATAN2_fast(position.x-relPlayerPos.x,position.z-relPlayerPos.z)+PI;
                        if(mainAngle != playerAngle)
                        {
                            mainAngle += sinf(playerAngle-mainAngle)*0.1f;
                        }
                        headAngleY = playerAngle-mainAngle;

                        if(distanceToPlayer > 1.5f)
                        {
                            TryToMove(Vector3(sinf(mainAngle),0.0f,cosf(mainAngle)),SPD*dt);
                        }

                        headAngleZ = (relPlayerPos.y-position.y-0.315f)*0.25f;
                        if(headAngleZ > PI/4.0f)
                        {
                            headAngleZ = PI/4.0f;
                        }
                        if(headAngleZ < -PI/4.0f)
                        {
                            headAngleZ = -PI/4.0f;
                        }
                    }
                    /// * --- END


                    /// HAUNTING --- *
                    if(haunting == true)
                    {
                        if(hauntingPos.x != 0 && hauntingPos.z != 0)
                        {
                            if(DistanceToHauntingPos() > 0.5f)
                            {
                                if(hauntingPos != Vector3(-1,-1,-1))
                                {
                                    //mainAngle = hauntingAngle;

                                    if(mainAngle != hauntingAngle)
                                    {
                                        mainAngle += sinf(hauntingAngle-mainAngle)*0.07f;
                                    }

                                    TryToMove(Vector3(sinf(mainAngle),0.0f,cosf(mainAngle)),SPD*dt);
                                }
                                else
                                {
                                    if(mainAngle != hauntingAngle)
                                    {
                                        mainAngle += sinf(hauntingAngle-mainAngle)*0.07f;
                                    }

                                    if(abs(mainAngle - hauntingAngle) < 0.02f)
                                    {
                                        mainAngle = hauntingAngle;
                                    }
                                }
                            }
                            else
                            {
                                hauntingPos.x = 0;
                                hauntingPos.z = 0;
                            }
                        }
                    }
                }
                /// * --- END


                /// MOVING WHEN KICKED ---- *
                if(kicked == true)
                {
                    mainAngle = ATAN2_fast(position.x-relPlayerPos.x,position.z-relPlayerPos.z)+PI; // super secret function
                    float angle;
                    if(lastKickType != 2)
                    {
                        angle = ATAN2_fast(position.x-relPlayerPos.x,position.z-relPlayerPos.z)+PI;
                    }
                    else
                    {
                        angle = ATAN2_fast(position.x-explosionPos.x,position.z-explosionPos.z)+PI;
                    }
                    TryToMoveWithoutJump(Vector3(sinf(angle+PI),0.0f,cosf(angle+PI)),(SPD+0.18f)*9.2f*(damagedTimer*damagedTimer)*dt);

                    if((walkingOnGround == true || footInLava || footInWater) && damagedTimer <= 0.0f)
                    {
                        kicked = false;
                    }

                    float playerAngle = ATAN2_fast(position.x-relPlayerPos.x,position.z-relPlayerPos.z)+PI;
                    headAngleY = playerAngle-mainAngle;

                    headAngleZ = (relPlayerPos.y-position.y-0.315f)*0.25f;
                    if(headAngleZ > PI/4.0f)
                    {
                        headAngleZ = PI/4.0f;
                    }
                    if(headAngleZ < -PI/4.0f)
                    {
                        headAngleZ = -PI/4.0f;
                    }
                }
                /// * --- END



                /// ANIMATIONS  --- *
                if(killed == false)
                {
                    animHandAngleT += PI*dt*0.75;
                    if(animHandAngleT >= PI*2)
                    {
                        animHandAngleT = 0.0f;
                    }
                    animHandAngle = sinf(animHandAngleT) * 0.09f;

                    if(moving == true)
                    {
                        animLegAngleT += PI*dt*1.6;
                        if(animLegAngleT >= PI*2)
                        {
                            animLegAngleT = 0.0f;
                        }
                    }
                    else
                    {
                        if (animLegAngleT > 0 && animLegAngleT < PI/2)
                        {
                            animLegAngleT -= animLegAngleT * 0.3f;
                            if (animLegAngleT < 0.05)
                            {
                                animLegAngleT = 0;
                            }
                        }
                        if (animLegAngleT >= PI/2 && animLegAngleT < PI)
                        {
                            animLegAngleT += (PI-animLegAngleT) * 0.3f;
                            if (animLegAngleT > PI - 0.05)
                            {
                                animLegAngleT = 0;
                            }
                        }
                        if (animLegAngleT > PI && animLegAngleT < PI*1.5)
                        {
                            animLegAngleT -= (animLegAngleT-PI) * 0.3f;
                            if (animLegAngleT < PI + 0.05)
                            {
                                animLegAngleT = 0;
                            }
                        }
                        if (animLegAngleT >= PI*1.5 && animLegAngleT < PI*2)
                        {
                            animLegAngleT += (2*PI-animLegAngleT) * 0.3f;
                            if (animLegAngleT > 2*PI - 0.05)
                            {
                                animLegAngleT = 0;
                            }
                        }
                    }
                    animLegAngle = sinf(animLegAngleT) * 0.7f;
                }
                /// * --- END


                /// DAMAGE FACTORS --- *
                if(touchingCactus)
                {
                    tickCactusDamage += dt;
                }
                else
                {
                    tickCactusDamage = 0.4f;
                }
                if(tickCactusDamage >= 0.5f)
                {
                    HP -= 1;
                    damaged = true;
                    damagedTimer = 0.55f;

                    tickCactusDamage -= 0.5f;
                }
                /// * --- END


                /// SIMEPLE MOB PHYSICS --- *

                Vector3 footPosition = position + foot;
                Vector3 legsPosition = position + legs;
                Vector3 headPosition = position + head;

                if(world->PlayerInWater(legsPosition))
                    footInWater = true;
                else
                    footInWater = false;

                if(world->PlayerInWater(headPosition))
                {
                    if (velocity.y > -3)
                    {
                        velocity.y += (GRAVITY/3.0f) * dt;
                    }
                    else
                    {
                        velocity.y = -3;
                    }
                    headInWater = true;
                }
                else
                {
                    headInWater = false;
                    velocity.y += (GRAVITY*1.3 * dt) * 1.6f;
                }

                if(world->PlayerInLava(legsPosition))
                {
                    footInLava = true;
                    HP -= 0.5f;
                    damaged = true;
                    damagedTimer = 0.55f;
                }
                else
                {
                    footInLava = false;
                }

                if(world->PlayerInLava(headPosition))
                {
                    velocity.y += (GRAVITY/3.0f) * dt;
                    headInLava = true;
                    HP -= 1;
                    damaged = true;
                    damagedTimer = 0.55f;
                }
                else
                {
                    headInLava = false;
                    velocity.y += GRAVITY * dt;
                }

                touchingCactus = false;
                if(world->PlayerCollisionWithCactus(headPosition) || world->PlayerCollisionWithCactus(legsPosition))
                {
                    touchingCactus = true;
                }

                if(world->SolidAtPointForEntity(footPosition,colliderD) || world->SolidAtPointForEntity(headPosition,colliderU))
                {
                    walkingOnGround = true;
                    if (world->SolidAtPointForEntity(headPosition,colliderU))
                    {
                        int blockIn = (int)(headPosition.y);
                        position.y = (float)(blockIn - colliderU.y - 0.05);
                    }
                    if (world->SolidAtPointForEntity(footPosition,colliderD))
                    {
                        int blockOn = (int)(footPosition.y);
                        position.y = (float)(blockOn + 1 + colliderD.y - 0.05);

                        if(world->GetBlock(footPosition.x,footPosition.y,footPosition.z) == CactusBlock::getID())
                        {
                            touchingCactus = true;
                        }
                    }

                    if(velocity.y != 0.0f) /// FALL DAMAGE
                    {
                        if (!world->PlayerInWater(footPosition))
                        {
                            if(velocity.y < -12 && velocity.y > -19)
                            {
                                HP -= (int)((velocity.y*-1) - 11) / 1.4;

                                damaged = true;
                                damagedTimer = 0.75f;
                                playHurtSound = true;
                            }
                            if(velocity.y < -19)
                            {
                                HP -= (int)((velocity.y*-1) - 11) * 1.3f;

                                damaged = true;
                                damagedTimer = 0.75f;
                                playHurtSound = true;
                            }
                        }
                    }
                    velocity.y = 0.0f;

                    if(jumping == true)
                    {
                        velocity.y = 1.55f * JUMPVELOCITY;
                        jumping = false;
                        walkingOnGround = false;
                    }
                }
                else
                {
                    walkingOnGround = false;
                }
                position += velocity * dt;
            }
            /// * --- END


        }
        else
        {
            if(dt < 0.1f)
            {
                freezedTimer += dt;
                if(freezedTimer >= 60.0f)
                {
                    toDestroy = true;
                }
            }
        }
    }
}

void Enderman::Render(Frustum &camFrustum, float dt)
{
    if(toDestroy == false)
    {
        if(fastDistanceToPlayer < world->mainOptions.horizontalViewDistance*14 && camFrustum.BoxInFrustum(bBox) == Frustum::Intersects)
        {
            sceGumPushMatrix();

            ScePspFVector3 loc22 = {position.x,position.y,position.z};
            sceGumTranslate(&loc22);

            sceGumRotateZ(0.0f);
            sceGumRotateY(mainAngle-PI/2);

            if(killed == true)
            {
                sceGumRotateX(deathAngle);
            }
            else
            {
                sceGumRotateX(0.0f);
            }

            updateLightTimer += dt;
            if(updateLightTimer > 0.25f)
            {
                updateLightTimer = 0.0f;
                myLight = world->BlockFinalLight(position.x,position.y+1,position.z);
            }

            if((damaged == true && damagedTimer > 0.25f) || killed == true)
            {
                sceGuColor(GU_COLOR(0.8f,0.1,0.1,1.0f));
            }
            else
            {
                sceGuColor(GU_COLOR(myLight,myLight,myLight,1.0f));
            }

            TextureManager::Instance()->SetTextureModeulate(mainTexture);

            sceGuEnable(GU_TEXTURE_2D);
            sceGuEnable(GU_DEPTH_TEST);
            sceGuDisable(GU_ALPHA_TEST);
            sceGuEnable(GU_BLEND);;


            sceGumPushMatrix();
            ScePspFVector3 loc = {0,0,0};
            sceGumTranslate(&loc);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->bodyVertices);
            sceGumPopMatrix();



            sceGumPushMatrix();
            ScePspFVector3 loc2 = {0,PIXEL*10,0};
            sceGumTranslate(&loc2);

            sceGumRotateX(0.0f);
            sceGumRotateY(headAngleY);
            sceGumRotateZ(headAngleZ);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->headVertices);
            sceGumPopMatrix();




            sceGumPushMatrix();
            ScePspFVector3 loc3 = {0,PIXEL*4,PIXEL*6};
            sceGumTranslate(&loc3);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
            sceGumRotateZ(rHandAngle-animHandAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->handVertices);
            sceGumPopMatrix();




            sceGumPushMatrix();
            ScePspFVector3 loc4 = {0,PIXEL*4,-PIXEL*6};
            sceGumTranslate(&loc4);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
            sceGumRotateZ(lHandAngle+animHandAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->handVertices);
            sceGumPopMatrix();



            sceGumPushMatrix();
            ScePspFVector3 loc5 = {0,-PIXEL*8,PIXEL*2};
            sceGumTranslate(&loc5);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
            sceGumRotateZ(rLegAngle+animLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->legVertices);
            sceGumPopMatrix();




            sceGumPushMatrix();
            ScePspFVector3 loc6 = {0,-PIXEL*8,-PIXEL*2};
            sceGumTranslate(&loc6);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
            sceGumRotateZ(lLegAngle-animLegAngle);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->legVertices);
            sceGumPopMatrix();


            DrawSetCulling(false);


           
            //sceGuDisable(GU_ALPHA_TEST);
            sceGuDisable(GU_DEPTH_TEST);
            sceGuDisable(GU_TEXTURE_2D);
            sceGuColor(0xFFFFFFFF);

            sceGumPopMatrix();
        }
    }
}