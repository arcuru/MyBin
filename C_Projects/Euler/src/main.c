#include "Euler.h"
#include "Euler_List.h"
#include "Utils.h"
#include <stdlib.h>
#include <stdio.h>

static void Fill_Euler_FunctionArray();
static int64_t (*Euler[301])() = {NULL};
static int suppress_time=false;

static void Euler_Compute_Ans(int number)
{
    float start, end;
    start = GetSecondClock();
    int64_t ans= Euler[number]();
    end = GetSecondClock();
    if (ans != 0) {
        float time = end - start;
        if (time < 0)
            time *= -1;
        if (suppress_time)
            time=0;
        printf("%d:\t%.3f\t%jd\n", number, time, ans);
    }
    return;
}

int main(int argc, char* argv[])
{
    Fill_Euler_FunctionArray();
    if (argc > 1) {
        int i;
        for (i = 1; i < argc; i++) {
            if ('t'==*argv[i]) {
                suppress_time=true;
                continue;
            }
            int tmp = atoi(argv[i]);
            if (tmp > 0 && tmp < 301) {
                Euler_Compute_Ans(tmp);
            }
            if (*argv[i] == '-' && atoi(argv[i - 1]) && atoi(argv[i + 1])) {
                int n;
                for (n = 1 + atoi(argv[i - 1]); n < atoi(argv[i + 1]); n++)
                    Euler_Compute_Ans(n);
            }
        }
        if (!suppress_time)
            return 0;
    }
    int i;
    for (i = 1; i <= 300; i++) {
        Euler_Compute_Ans(i);
    }
    return EXIT_SUCCESS;
}

static void Fill_Euler_FunctionArray()
{
    Euler[1] = &Euler_1;
    Euler[2] = &Euler_2;
    Euler[3] = &Euler_3;
    Euler[4] = &Euler_4;
    Euler[5] = &Euler_5;
    Euler[6] = &Euler_6;
    Euler[7] = &Euler_7;
    Euler[8] = &Euler_8;
    Euler[9] = &Euler_9;
    Euler[10] = &Euler_10;
    Euler[11] = &Euler_11;
    Euler[12] = &Euler_12;
    Euler[13] = &Euler_13;
    Euler[14] = &Euler_14;
    Euler[15] = &Euler_15;
    Euler[16] = &Euler_16;
    Euler[17] = &Euler_17;
    Euler[18] = &Euler_18;
    Euler[19] = &Euler_19;
    Euler[20] = &Euler_20;
    Euler[21] = &Euler_21;
    Euler[22] = &Euler_22;
    Euler[23] = &Euler_23;
    Euler[24] = &Euler_24;
    Euler[25] = &Euler_25;
    Euler[26] = &Euler_26;
    Euler[27] = &Euler_27;
    Euler[28] = &Euler_28;
    Euler[29] = &Euler_29;
    Euler[30] = &Euler_30;
    Euler[31] = &Euler_31;
    Euler[32] = &Euler_32;
    Euler[33] = &Euler_33;
    Euler[34] = &Euler_34;
    Euler[35] = &Euler_35;
    Euler[36] = &Euler_36;
    Euler[37] = &Euler_37;
    Euler[38] = &Euler_38;
    Euler[39] = &Euler_39;
    Euler[40] = &Euler_40;
    Euler[41] = &Euler_41;
    Euler[42] = &Euler_42;
    Euler[43] = &Euler_43;
    Euler[44] = &Euler_44;
    Euler[45] = &Euler_45;
    Euler[46] = &Euler_46;
    Euler[47] = &Euler_47;
    Euler[48] = &Euler_48;
    Euler[49] = &Euler_49;
    Euler[50] = &Euler_50;
    Euler[51] = &Euler_51;
    Euler[52] = &Euler_52;
    Euler[53] = &Euler_53;
    Euler[54] = &Euler_54;
    Euler[55] = &Euler_55;
    Euler[56] = &Euler_56;
    Euler[57] = &Euler_57;
    Euler[58] = &Euler_58;
    Euler[59] = &Euler_59;
    Euler[60] = &Euler_60;
    Euler[61] = &Euler_61;
    Euler[62] = &Euler_62;
    Euler[63] = &Euler_63;
    Euler[64] = &Euler_64;
    Euler[65] = &Euler_65;
    Euler[66] = &Euler_66;
    Euler[67] = &Euler_67;
    Euler[68] = &Euler_68;
    Euler[69] = &Euler_69;
    Euler[70] = &Euler_70;
    Euler[71] = &Euler_71;
    Euler[72] = &Euler_72;
    Euler[73] = &Euler_73;
    Euler[74] = &Euler_74;
    Euler[75] = &Euler_75;
    Euler[76] = &Euler_76;
    Euler[77] = &Euler_77;
    Euler[78] = &Euler_78;
    Euler[79] = &Euler_79;
    Euler[80] = &Euler_80;
    Euler[81] = &Euler_81;
    Euler[82] = &Euler_82;
    Euler[83] = &Euler_83;
    Euler[84] = &Euler_84;
    Euler[85] = &Euler_85;
    Euler[86] = &Euler_86;
    Euler[87] = &Euler_87;
    Euler[88] = &Euler_88;
    Euler[89] = &Euler_89;
    Euler[90] = &Euler_90;
    Euler[91] = &Euler_91;
    Euler[92] = &Euler_92;
    Euler[93] = &Euler_93;
    Euler[94] = &Euler_94;
    Euler[95] = &Euler_95;
    Euler[96] = &Euler_96;
    Euler[97] = &Euler_97;
    Euler[98] = &Euler_98;
    Euler[99] = &Euler_99;
    Euler[100] = &Euler_100;
    Euler[101] = &Euler_101;
    Euler[102] = &Euler_102;
    Euler[103] = &Euler_103;
    Euler[104] = &Euler_104;
    Euler[105] = &Euler_105;
    Euler[106] = &Euler_106;
    Euler[107] = &Euler_107;
    Euler[108] = &Euler_108;
    Euler[109] = &Euler_109;
    Euler[110] = &Euler_110;
    Euler[111] = &Euler_111;
    Euler[112] = &Euler_112;
    Euler[113] = &Euler_113;
    Euler[114] = &Euler_114;
    Euler[115] = &Euler_115;
    Euler[116] = &Euler_116;
    Euler[117] = &Euler_117;
    Euler[118] = &Euler_118;
    Euler[119] = &Euler_119;
    Euler[120] = &Euler_120;
    Euler[121] = &Euler_121;
    Euler[122] = &Euler_122;
    Euler[123] = &Euler_123;
    Euler[124] = &Euler_124;
    Euler[125] = &Euler_125;
    Euler[126] = &Euler_126;
    Euler[127] = &Euler_127;
    Euler[128] = &Euler_128;
    Euler[129] = &Euler_129;
    Euler[130] = &Euler_130;
    Euler[131] = &Euler_131;
    Euler[132] = &Euler_132;
    Euler[133] = &Euler_133;
    Euler[134] = &Euler_134;
    Euler[135] = &Euler_135;
    Euler[136] = &Euler_136;
    Euler[137] = &Euler_137;
    Euler[138] = &Euler_138;
    Euler[139] = &Euler_139;
    Euler[140] = &Euler_140;
    Euler[141] = &Euler_141;
    Euler[142] = &Euler_142;
    Euler[143] = &Euler_143;
    Euler[144] = &Euler_144;
    Euler[145] = &Euler_145;
    Euler[146] = &Euler_146;
    Euler[147] = &Euler_147;
    Euler[148] = &Euler_148;
    Euler[149] = &Euler_149;
    Euler[150] = &Euler_150;
    Euler[151] = &Euler_151;
    Euler[152] = &Euler_152;
    Euler[153] = &Euler_153;
    Euler[154] = &Euler_154;
    Euler[155] = &Euler_155;
    Euler[156] = &Euler_156;
    Euler[157] = &Euler_157;
    Euler[158] = &Euler_158;
    Euler[159] = &Euler_159;
    Euler[160] = &Euler_160;
    Euler[161] = &Euler_161;
    Euler[162] = &Euler_162;
    Euler[163] = &Euler_163;
    Euler[164] = &Euler_164;
    Euler[165] = &Euler_165;
    Euler[166] = &Euler_166;
    Euler[167] = &Euler_167;
    Euler[168] = &Euler_168;
    Euler[169] = &Euler_169;
    Euler[170] = &Euler_170;
    Euler[171] = &Euler_171;
    Euler[172] = &Euler_172;
    Euler[173] = &Euler_173;
    Euler[174] = &Euler_174;
    Euler[175] = &Euler_175;
    Euler[176] = &Euler_176;
    Euler[177] = &Euler_177;
    Euler[178] = &Euler_178;
    Euler[179] = &Euler_179;
    Euler[180] = &Euler_180;
    Euler[181] = &Euler_181;
    Euler[182] = &Euler_182;
    Euler[183] = &Euler_183;
    Euler[184] = &Euler_184;
    Euler[185] = &Euler_185;
    Euler[186] = &Euler_186;
    Euler[187] = &Euler_187;
    Euler[188] = &Euler_188;
    Euler[189] = &Euler_189;
    Euler[190] = &Euler_190;
    Euler[191] = &Euler_191;
    Euler[192] = &Euler_192;
    Euler[193] = &Euler_193;
    Euler[194] = &Euler_194;
    Euler[195] = &Euler_195;
    Euler[196] = &Euler_196;
    Euler[197] = &Euler_197;
    Euler[198] = &Euler_198;
    Euler[199] = &Euler_199;
    Euler[200] = &Euler_200;
    Euler[201] = &Euler_201;
    Euler[202] = &Euler_202;
    Euler[203] = &Euler_203;
    Euler[204] = &Euler_204;
    Euler[205] = &Euler_205;
    Euler[206] = &Euler_206;
    Euler[207] = &Euler_207;
    Euler[208] = &Euler_208;
    Euler[209] = &Euler_209;
    Euler[210] = &Euler_210;
    Euler[211] = &Euler_211;
    Euler[212] = &Euler_212;
    Euler[213] = &Euler_213;
    Euler[214] = &Euler_214;
    Euler[215] = &Euler_215;
    Euler[216] = &Euler_216;
    Euler[217] = &Euler_217;
    Euler[218] = &Euler_218;
    Euler[219] = &Euler_219;
    Euler[220] = &Euler_220;
    Euler[221] = &Euler_221;
    Euler[222] = &Euler_222;
    Euler[223] = &Euler_223;
    Euler[224] = &Euler_224;
    Euler[225] = &Euler_225;
    Euler[226] = &Euler_226;
    Euler[227] = &Euler_227;
    Euler[228] = &Euler_228;
    Euler[229] = &Euler_229;
    Euler[230] = &Euler_230;
    Euler[231] = &Euler_231;
    Euler[232] = &Euler_232;
    Euler[233] = &Euler_233;
    Euler[234] = &Euler_234;
    Euler[235] = &Euler_235;
    Euler[236] = &Euler_236;
    Euler[237] = &Euler_237;
    Euler[238] = &Euler_238;
    Euler[239] = &Euler_239;
    Euler[240] = &Euler_240;
    Euler[241] = &Euler_241;
    Euler[242] = &Euler_242;
    Euler[243] = &Euler_243;
    Euler[244] = &Euler_244;
    Euler[245] = &Euler_245;
    Euler[246] = &Euler_246;
    Euler[247] = &Euler_247;
    Euler[248] = &Euler_248;
    Euler[249] = &Euler_249;
    Euler[250] = &Euler_250;
    Euler[251] = &Euler_251;
    Euler[252] = &Euler_252;
    Euler[253] = &Euler_253;
    Euler[254] = &Euler_254;
    Euler[255] = &Euler_255;
    Euler[256] = &Euler_256;
    Euler[257] = &Euler_257;
    Euler[258] = &Euler_258;
    Euler[259] = &Euler_259;
    Euler[260] = &Euler_260;
    Euler[261] = &Euler_261;
    Euler[262] = &Euler_262;
    Euler[263] = &Euler_263;
    Euler[264] = &Euler_264;
    Euler[265] = &Euler_265;
    Euler[266] = &Euler_266;
    Euler[267] = &Euler_267;
    Euler[268] = &Euler_268;
    Euler[269] = &Euler_269;
    Euler[270] = &Euler_270;
    Euler[271] = &Euler_271;
    Euler[272] = &Euler_272;
    Euler[273] = &Euler_273;
    Euler[274] = &Euler_274;
    Euler[275] = &Euler_275;
    Euler[276] = &Euler_276;
    Euler[277] = &Euler_277;
    Euler[278] = &Euler_278;
    Euler[279] = &Euler_279;
    Euler[280] = &Euler_280;
    Euler[281] = &Euler_281;
    Euler[282] = &Euler_282;
    Euler[283] = &Euler_283;
    Euler[284] = &Euler_284;
    Euler[285] = &Euler_285;
    Euler[286] = &Euler_286;
    Euler[287] = &Euler_287;
    Euler[288] = &Euler_288;
    Euler[289] = &Euler_289;
    Euler[290] = &Euler_290;
    Euler[291] = &Euler_291;
    Euler[292] = &Euler_292;
    Euler[293] = &Euler_293;
    Euler[294] = &Euler_294;
    Euler[295] = &Euler_295;
    Euler[296] = &Euler_296;
    Euler[297] = &Euler_297;
    Euler[298] = &Euler_298;
    Euler[299] = &Euler_299;
    Euler[300] = &Euler_300;
    return;
}
