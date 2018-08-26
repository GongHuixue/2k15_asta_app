/**********************************************************************
 *
 *   C Source:       hsvdvbtmpegins_m.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    nareshj %
 *   %date_created:  Tue Mar 06 21:05:01 2012 %
 *
 **********************************************************************/
#include "_hsvdvbtmpegins_m.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbtmpegins_m")






















HsvInstallationSpectrum CHsvDvbtMpegInstallation_m_Priv::s__AntennaSpectrum[ANTENNASPECTRUM_ENTRIES][MAX_BANDS] =
{
    /* Austria    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Belgium    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Croatia    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Czechrep   */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Denmark    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Finland    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* France     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_298,           BAND_466,           BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Germany    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Greece     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Hungary    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Ireland    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Italy      */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Luxembourg */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Netherlands*/    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Norway     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_226_00_8MHz,   BAND_226_50_7MHz,   BAND_298,   BAND_466,   BAND_NULL},
    /* Poland     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Portugal   */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Romania    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Russia     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Serbia     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Slovakia   */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Slovenia   */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Spain      */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Sweden     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Switzerland*/    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Turkey     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* UK         */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Other      */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Australia  */    {  BAND_170_AUS,        BAND_515_AUS,       BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Estonia    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Lithuania  */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Latvia      */    {  BAND_170_50_7MHz,   BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Kazakhstan */     {  BAND_170_50_7MHz,   BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Bulgaria   */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* China      */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Ukraine    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Brazil     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Argentina  */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Albania    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Armenia    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Azerbaijan */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Belarus    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Bos+Herz   */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Georgia    */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Montenegro */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Israel     */    {  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* Macedoniafyrom */{  BAND_170_50_7MHz,    BAND_170_00_8MHz,   BAND_171_00_8MHz,   BAND_177_50_7MHz,   BAND_178_00_8MHz,   BAND_179_00_7MHz,   BAND_179_00_8MHz,   BAND_184_50_7MHz,   BAND_186_00_8MHz,   BAND_187_00_8MHz,   BAND_187_50_7MHz,   BAND_191_50_7MHz,   BAND_194_00_8MHz,   BAND_195_00_8MHz,   BAND_196_50_7MHz,   BAND_198_50_7MHz,   BAND_202_00_8MHz,   BAND_203_00_8MHz,   BAND_205_50_7MHz,   BAND_210_00_8MHz,   BAND_211_00_8MHz,   BAND_212_50_7MHz,   BAND_218_00_8MHz,   BAND_219_50_7MHz,   BAND_466,           BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL},
    /* DvbcLight  */    {  BAND_DVBCLIGHT_7MHZ, BAND_DVBCLIGHT_8MHZ,BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,          BAND_NULL,  BAND_NULL,  BAND_NULL}
};


HsvInstallationSpectrum CHsvDvbtMpegInstallation_m_Priv::s__CableSpectrum[CABLESPECTRUM_ENTRIES] = {BAND_DVBCLIGHT_7MHZ,  BAND_DVBCLIGHT_8MHZ, BAND_NULL};



#ifndef __cplusplus

#else

#endif




Bool CHsvDvbtMpegInstallation_m_Priv::s__InstallationInitialised = FALSE;

Bool CHsvDvbtMpegInstallation_m_Priv::s__InstallationTurnOn = FALSE;

Pump CHsvDvbtMpegInstallation_m_Priv::s__mDVBTMpegPump;








TypeDigitalInstallationStatus CHsvDvbtMpegInstallation_m_Priv::s__mDvbtMpegStatus;


/****************************************************************************
 * Local function declarations
 ****************************************************************************/
/*Event Action functions*/









Bool CHsvDvbtMpegInstallation_m_Priv::s__mPATReceived = FALSE;























#undef  DECLARECONVERTFUNC


    



const FunctionNat32 CHsvDvbtMpegInstallation_m_Priv::mDvbtMpegMatrix[evMax][StMax] =
{
						   /*  StIdle                StFeWait                StDmxWait            StDecision   */
    /*evStart*/           {FNADDR(FuncStartDigitalScan),    NULL,                   NULL,                NULL             },
    /*evStop*/            {NULL,                    FNADDR(FuncStop),               FNADDR(FuncStop),            FNADDR(FuncStop)         },
    /*evMeasNtfSigStr*/   {NULL,                    FNADDR(FuncSigStrMeasured),     FNADDR(FuncSigStrMeasured),  NULL             },
    /*evPgDatAvailable*/  {FNADDR(FuncDmxData),             NULL,                   FNADDR(FuncDmxData),         NULL             },
    /*evStationFound*/    {NULL,                    FNADDR(FuncStationFound),       NULL,                NULL             },
    /*evStationNotFound*/ {NULL,                    FNADDR(FuncStationNotFound),    NULL,                NULL             },
    /*evMakeDecision*/    {NULL,                    NULL,                   NULL,                FNADDR(FuncMakeDecision) },
    /*evPATTimeOut    */  {NULL,                    NULL,                   FNADDR(FuncDmxData),         NULL             },
	/*evOnMeasReady*/     {NULL,                    NULL,					FNADDR(FuncOnMeasReady),	 FNADDR(FuncOnMeasReady)  }
};


/****************************************************************************
 * Function definitions
 ****************************************************************************/

void CHsvDvbtMpegInstallation_m_Priv::pow_Init(void)
{
    mDVBTMpegPump = pmp_PmpCreateEx( pen_PumpEngine, mDvbtMpegHandler, FALSE,"hsvdvbtmpeg_m.pmp" );
    InstallationInitialised = TRUE;
}


void CHsvDvbtMpegInstallation_m_Priv::pow_TurnOn(void)
{
    ASSERT(InstallationInitialised);

    if( InstallationInitialised )
    {
        InstallationTurnOn = TRUE;
    }
    else
    {
        instutil_LogError( log_SoftErr, INS_INVALID_TURNON ); /*log the error */
    }
}

void CHsvDvbtMpegInstallation_m_Priv::pow_TurnOff(void)
{
    InstallationTurnOn = FALSE;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_Initialise(void)
{
    mDvbtMpegStatus.ModulationType        =   HsvAutoConstellation;
    mDvbtMpegStatus.CodeRateHigh          =   HsvCodeRateAuto;
    mDvbtMpegStatus.CodeRateLow           =   HsvCodeRateAuto;
    mDvbtMpegStatus.HierarchyMode         =   HsvHierarchyModeAuto;
    mDvbtMpegStatus.HierarchyModeDetected =   FALSE;
    mDvbtMpegStatus.GuardInterval         =   HsvGuardIntervalAuto;
    mDvbtMpegStatus.TxMode                =   HsvTxModeAuto;
    mDvbtMpegStatus.IqMode                =   HsvIqModeNormal;
    mDvbtMpegStatus.ChannelBandwidth      =   tmFe_ChanBandwidth8MHz;//HsvChanBandwidth8MHz;
    mDvbtMpegStatus.StreamPriority        =   HsvStreamPriorityHigh;
    mDvbtMpegStatus.ChannelInformation    =   0;
    mDvbtMpegStatus.TimeError             =   0;
    mDvbtMpegStatus.FrequencyError        =   0;
    mDvbtMpegStatus.FrequencyOffset       =   HsvOffsetNone;
    mDvbtMpegStatus.CurrentDemux          =   HsvDmxMain;         /*default dmux*/
    mDvbtMpegStatus.FrequencyBand         =   0;
    mDvbtMpegStatus.PlayStarted           =   FALSE;
    mDvbtMpegStatus.StationFound          =   FALSE;
    mDvbtMpegStatus.Country               =   sysset_GetSystemCountry();

    idigacq_Initialise();
}

void CHsvDvbtMpegInstallation_m_Priv::UpdateDigitalTunerInstallationStatus(void)
{
    Nat32 errorcode = TM_OK;

    feapi_GetFreq(WINDOWID,&mDvbtMpegStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode );

    {
        tmFe_Constellation_t param1;
        feapi_GetActualConstellation (WINDOWID,feapi_ChanDecDvbT,&param1,&errorcode);
        ASSERT(TM_OK  ==  errorcode);
        mDvbtMpegStatus.ModulationType = param1; //(Nat8 )ConvertFromPlatformConstellation(param1);
    }

    {
        tmFe_ChanBandwidth_t param1;
        feapi_GetActualChanBandwidth (WINDOWID, &param1, &errorcode);
        ASSERT(TM_OK  ==  errorcode);
        mDvbtMpegStatus.ChannelBandwidth = param1;//(Nat8 )ConvertFromPlatformChanBandwidth(param1);
    }


    {
        tmFe_StreamPriority_t param1;
        feapi_GetStreamPriority ( WINDOWID,&param1, &errorcode);
        ASSERT(TM_OK  ==  errorcode);
        mDvbtMpegStatus.StreamPriority = ConvertFromPlatformStreamPriority(param1);
    }

}

void CHsvDvbtMpegInstallation_m_Priv::SetChannelDecoderAttributes(void)
{
    Nat32 errorcode = TM_OK;
    tmFe_ChanBandwidth_t   Bandwidth = (MANUAL_INSTALL)? tmFe_ChanBandwidthAuto: AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].Bandwidth;

    feapi_SetChanBandwidth ( WINDOWID, Bandwidth, &errorcode );
    ASSERT(TM_OK == errorcode);

    feapi_SetConstellation(WINDOWID,feapi_ChanDecDvbT,tmFe_AutoConstellation, &errorcode);
    ASSERT(TM_OK == errorcode);

}


/* Pump functions Called for every event which can occur */
/****************************************************************************
 *Function   :
 *Description:
 *Parameters :
 *****************************************************************************/
void CHsvDvbtMpegInstallation_m_Priv::mDvbtMpegHandler(int event, Nat32 param2)
{
    TraceDebug(m,"dvbtmpegins.c: %d: %s: event = %d, state = %d ", __LINE__, __FUNCTION__,event,mDvbtMpegStatus.State);

    if(InstallationTurnOn )
    {
        if(mDvbtMpegMatrix[event][mDvbtMpegStatus.State] != NULL)
        {
            FPCALL(mDvbtMpegMatrix[event][mDvbtMpegStatus.State])(param2);
        }
    }
}

/****************************************************************************
 *Function   :
 *Description:
 *Parameters :
 *****************************************************************************/

void CHsvDvbtMpegInstallation_m_Priv::FuncStartDigitalScan(Nat32 param)
{
    Nat32 errorcode = TM_OK;

    if(MANUAL_INSTALL)
    {
        TraceDebug(m,"%s %d Manual Install Started with Freq : %d", __FUNCTION__, __LINE__, (int)param);
        idigscan_StartDigitalTuning(param);
    }
    else
    {
    	/*Clear the Databases*/
		if(AUTO_INSTALL)
		{
			pgdb_ClearTable(ANTENNA_SERVICE);
			pgdb_ClearTable(ANTENNA_PTC);
			pgdb_ClearTable(ANTENNA_PRESET);
		}

        TraceDebug(m,"%s %d param : %d", __FUNCTION__, __LINE__, (int)param);
        if( param < (Nat32)AntennaSpectrum[mDvbtMpegStatus.Country][0].StartFrequency )
        {
            param = AntennaSpectrum[mDvbtMpegStatus.Country][0].StartFrequency;
        }
        else
        {
            if (param > (Nat32)mGetMaxFrequency(AntennaSpectrum[mDvbtMpegStatus.Country]))
            {
                param = mGetMaxFrequency(AntennaSpectrum[mDvbtMpegStatus.Country]);
            }
        }

        mDvbtMpegStatus.Frequency = mGetCorrectedFrequency(param, mDvbtMpegStatus.Country);

        ctrl_StopCollection(mDvbtMpegStatus.CurrentDemux);

        SetChannelDecoderAttributes();


        mDvbtMpegStatus.State      =   StFeWait;

        TraceDebug(m,"dvbtmpegins.c: %d: %s: Freq = %d", __LINE__, __FUNCTION__, AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].StartFrequency);

        //feapi_SetFreq ( WINDOWID, AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].StartFrequency, FALSE, &errorcode);
        //ASSERT(TM_OK == errorcode);

        feapi_StartSearch ( WINDOWID, AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].StartFrequency, tmFe_SmDefault, AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].EndFrequency, &errorcode );
        ASSERT(TM_OK == errorcode);
    }
}

void CHsvDvbtMpegInstallation_m_Priv::FuncStop(Nat32 param)
{
    tmErrorCode_t errorcode;

    TraceDebug(m,"%s",__FUNCTION__);

    switch(mDvbtMpegStatus.State)
    {
        case StFeWait:
            feapi_StopSearch(WINDOWID, &errorcode);
            ASSERT(TM_OK  ==  errorcode);
            break;
        case StDmxWait:
            ctrl_StopCollection(mDvbtMpegStatus.CurrentDemux);
            sigstr_StopSigStrMeasAll();
            break;
        case StDecision:
            /* pavan: Not possible actually. State change happens in Makedecision anyways */
            TraceDebug(m,"Nothing can be done ??");
            break;
        default:
            ASSERT(FALSE);
            break;
    }

    mDvbtMpegStatus.State = StIdle;
    insN_OnEvent(insN_EventInstallationStopped, CURRENT_MODE);
    UNUSED(param);
}

void CHsvDvbtMpegInstallation_m_Priv::FuncDmxData(Nat32 param)
{
    TraceDebug(m,"dvbtmpeg: %s: %d",__FUNCTION__,__LINE__);

    UNUSED(param);

    switch ( CURRENT_MODE )
    {
        case BACKGROUND_MODE:

            TraceDebug(m,"dvbtmpeg: %s: %d",__FUNCTION__,__LINE__);
            UpdateDigitalTunerInstallationStatus();
            idigacq_AcquireData();
	    if (idigacq_IsNetworkUpdateDetected())
	    {
		    insN_OnEvent(insN_EventInstallationStarted, CURRENT_MODE);
		    insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);					
	    }
            mDvbtMpegStatus.State = StIdle;
            break;

        case AUTO_MODE:
        case UPDATE_MODE:

            TraceDebug(m,"dvbtmpeg: %s: %d",__FUNCTION__,__LINE__);

            mDvbtMpegStatus.State = StDecision;
            idigacq_AcquireData();
            sigstr_StopSigStrMeasAll();
            insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
            if(ctrl_GetMode(mDvbtMpegStatus.CurrentDemux)!=ctrl_Idle)
            {
                ctrl_StopCollection(mDvbtMpegStatus.CurrentDemux);
            }
            pmp_PmpSend(mDVBTMpegPump,evMakeDecision,mDvbtMpegStatus.Frequency);
            break;

        case MANUAL_MODE:
            TraceDebug(m,"dvbtmpeg: %s: %d",__FUNCTION__,__LINE__);
            insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
            break;
        default:
            TraceDebug(m,"dvbtmpeg: %s: %d",__FUNCTION__,__LINE__);
            break;
    }
}

void CHsvDvbtMpegInstallation_m_Priv::FuncStationFound(Nat32 param)
{
    Nat32 errorcode = TM_OK;
    
    feapi_GetFreq(WINDOWID,&mDvbtMpegStatus.Frequency, &errorcode);
    TraceDebug(m,"dvbtmpeg: %s: %d. Freq = %d",__FUNCTION__,__LINE__,(int)mDvbtMpegStatus.Frequency>>4);
    
    UNUSED(param);
    UpdateDigitalTunerInstallationStatus();

    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:

            mDvbtMpegStatus.State = StDmxWait;

            sigstr_SetSigStrengthMeasured(FALSE);
            sigstr_Initialise();
            sigstr_UpdateSigStrRange();
            sigstr_StartSigStrMeasAll();
            if(ctrl_GetMode(mDvbtMpegStatus.CurrentDemux)!=ctrl_Idle)
            {
                ctrl_StopCollection(mDvbtMpegStatus.CurrentDemux);
            }
            ctrl_StartCollection(mDvbtMpegStatus.CurrentDemux,ctrl_Minimal);
            ArmTimerForPAT();

            break;

        case MANUAL_MODE:

            mDvbtMpegStatus.State = StDmxWait;

            sigstr_StartSigStrMeasAll();

            pmp_PmpSend(mDVBTMpegPump, evMeasNtfSigStr, (Nat32)NULL);

            if( TRUE == sigstr_GetSigStrengthMeasured() )
            {
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigAssm);
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigSssm);
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigVssm);
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigQssm);
            }

            ctrl_StartCollection(mDvbtMpegStatus.CurrentDemux, ctrl_Normal);

            insN_OnEvent(insN_EventTuningStarted, CURRENT_MODE); 

            break;

        default:
            break;
    }
}

void CHsvDvbtMpegInstallation_m_Priv::FuncStationNotFound(Nat32 param)
{
    Nat32 errorcode = TM_OK;
    
    feapi_GetFreq(WINDOWID,&mDvbtMpegStatus.Frequency, &errorcode);
    TraceDebug(m,"dvbtmpeg: %s: %d. Freq = %d",__FUNCTION__,__LINE__,(int)mDvbtMpegStatus.Frequency>>4);

    UNUSED(param);
    if(MANUAL_INSTALL)
    {
        TraceDebug(m,"dvbtmpeg: %s: %d. ",__FUNCTION__,__LINE__);
        mDvbtMpegStatus.State = StIdle;
        insN_OnEvent(insN_EventChannelNotFound, MANUAL_MODE);
    }
    else
    {
        TraceDebug(m,"dvbtmpeg: %s: %d. ",__FUNCTION__,__LINE__);
        mDvbtMpegStatus.State = StDecision;
        pmp_PmpSend(mDVBTMpegPump,evMakeDecision,mDvbtMpegStatus.Frequency);
    }
}

void CHsvDvbtMpegInstallation_m_Priv::FuncMakeDecision(Nat32 param)
{
    Nat32 errorcode = TM_OK;

    TraceDebug(m,"dvbtmpegins.c: %d: %s: ", __LINE__, __FUNCTION__);

    UNUSED(param);

    switch (CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:

            if ((FALSE == mDvbtMpegStatus.StationFound ) || (mDvbtMpegStatus.Frequency >= (Nat32)AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].EndFrequency))
            {   /* Station Not Found or we are already at the last frequency. Now see if we can search the next band */
                int NextStartFrequency = INVALID_FREQUENCY;
                mDvbtMpegStatus.FrequencyBand++;

                if( INVALID_FREQUENCY  == (NextStartFrequency = AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].StartFrequency) )
                {
                    TraceDebug(m,"dvbtmpegins.c: %d: %s: ", __LINE__, __FUNCTION__);
                    mDvbtMpegStatus.State = StIdle;
                    insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
                }
                else
                {
                    int NextEndFrequency = AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].EndFrequency;
                    int NextChanBandwidth = AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].Bandwidth;

                    /* Start Search again */
                    TraceDebug(m,"dvbtmpegins.c: %d: %s: ", __LINE__, __FUNCTION__);
                    mDvbtMpegStatus.State = StFeWait;

                    feapi_SetChanBandwidth ( WINDOWID, (tmFe_ChanBandwidth_t)NextChanBandwidth, &errorcode);
                    ASSERT(TM_OK == errorcode);

                    //feapi_SetFreq ( WINDOWID, NextStartFrequency, FALSE, &errorcode);
                    //ASSERT(TM_OK == errorcode);

                    feapi_StartSearch ( WINDOWID, NextStartFrequency, tmFe_SmDefault, NextEndFrequency, &errorcode );
                    ASSERT(TM_OK == errorcode);
                }
            }
            else if(mDvbtMpegStatus.StationFound == TRUE)
            {
                /* Start Search again */
                TraceDebug(m,"dvbtmpegins.c: %d: %s: ", __LINE__, __FUNCTION__);
                mDvbtMpegStatus.State = StFeWait;

                /* This Change is made because offset value from platfrom is zero, when there was change in centre frequency*/
                mDvbtMpegStatus.Frequency = mGetCorrectedFrequency(mDvbtMpegStatus.Frequency, mDvbtMpegStatus.Country);
                //feapi_SetFreq ( WINDOWID, mDvbtMpegStatus.Frequency, FALSE, &errorcode);
                //ASSERT(TM_OK == errorcode);

                feapi_StartSearch ( WINDOWID, mDvbtMpegStatus.Frequency, tmFe_SmDefault, AntennaSpectrum[mDvbtMpegStatus.Country][mDvbtMpegStatus.FrequencyBand].EndFrequency, &errorcode );
                ASSERT(TM_OK == errorcode);
            }
            break;
        default:
            TraceDebug(m,"dvbtmpegins.c: %d: %s: ", __LINE__, __FUNCTION__);
            instutil_LogError( log_SoftErr, INS_INVALID_SWITCH_CASE ); /*log the error */
            break;
    }
}

void CHsvDvbtMpegInstallation_m_Priv::FuncSigStrMeasured(Nat32 param)
{
    TraceDebug(m,"dvbtmpegins.c: %d: %s: ", __LINE__, __FUNCTION__);

    if(TRUE == sigstr_StartSigStrMeasAll())
    {
        TraceDebug(m,"dvbtmpegins.c: %d: %s: ", __LINE__, __FUNCTION__);
        pmp_PmpSendAfter( mDVBTMpegPump,evMeasNtfSigStr,0, SIGSTR_WAITTIME);
    }
    UNUSED(param);
}

void CHsvDvbtMpegInstallation_m_Priv::FuncOnMeasReady(Nat32  param)
{
	if(TRUE == sigstr_GetSigStrengthMeasured()) 
    {
        pmp_PmpSend(mDVBTMpegPump,evMeasNtfSigStr,mDvbtMpegStatus.Frequency);
    }
}


FResult CHsvDvbtMpegInstallation_m_Priv::idigscan_StartInstallation(int source, int ptc, int mode)
{
    FResult retval = err_Ok;
    Nat32 ret, decoder;
    UNUSED(source);
    UNUSED(mode);


    if(AUTO_INSTALL || UPDATE_INSTALL || MANUAL_INSTALL)
    {
        if(StIdle == mDvbtMpegStatus.State)
        {
            pmp_PmpSend(mDVBTMpegPump,evStart, ptc);
        }
        else
        {
            retval = err_InstallationCommandNotAllowed;
        }
    }
    else
    {
        retval = err_InstallationModeNotSupported;
    }

    TraceDebug(m,"dvbtmpegins.c: %d: %s: retval = %d", __LINE__, __FUNCTION__,retval);

    return retval;
}

FResult CHsvDvbtMpegInstallation_m_Priv::idigscan_StartDigitalScan()
{
    return err_InstallationCommandNotAllowed;
}

FResult CHsvDvbtMpegInstallation_m_Priv::idigscan_StartDigitalTuning( int Frequency )
{
    FResult retval = err_Ok;
    Nat32 errorcode = TM_OK;
    int DirectFrequencyToBeSet = Frequency;

    if(Frequency < AntennaSpectrum[mDvbtMpegStatus.Country][0].StartFrequency)
    {
        Frequency = AntennaSpectrum[mDvbtMpegStatus.Country][0].StartFrequency;
    }
    else
    {
        if(Frequency > mGetMaxFrequency((HsvInstallationSpectrum*)(AntennaSpectrum[mDvbtMpegStatus.Country])))
        {
            Frequency = mGetMaxFrequency((HsvInstallationSpectrum*)(AntennaSpectrum[mDvbtMpegStatus.Country]));
        }
    }
    Frequency = mGetCorrectedFrequency(Frequency, mDvbtMpegStatus.Country);
    mDvbtMpegStatus.Frequency = Frequency;


    if(ctrl_GetMode(mDvbtMpegStatus.CurrentDemux)!=ctrl_Idle)
    {  /* Flush old data - irrespective of whether SDM is running */    
        ctrl_StopCollection(mDvbtMpegStatus.CurrentDemux);
    }    

    SetChannelDecoderAttributes();


    /* Setting Stream Priority */ 
    mDvbtMpegStatus.StreamPriority = HsvStreamPriorityHigh;
    SetStreamPriority(HsvStreamPriorityHigh);

    mDvbtMpegStatus.State = StFeWait;

    TraceDebug(m,"%s %d Manual Install : SetFreq with Freq : %d", __FUNCTION__, __LINE__, DirectFrequencyToBeSet);
    feapi_SetFreq ( WINDOWID, DirectFrequencyToBeSet, TRUE, &errorcode);
    ASSERT(TM_OK == errorcode);

    return retval;
}

FResult CHsvDvbtMpegInstallation_m_Priv::idigscan_StopDigitalScan (void)
{
    FResult retval  =  err_InstallationNotInProgress;

    if( InstallationTurnOn )
    {
        switch (mDvbtMpegStatus.State)
        {
            case StFeWait:
            case StDmxWait:
                pmp_PmpSend(mDVBTMpegPump,evStop,0);
                retval = err_Ok;
                break;
            default:
                break;
        }
    }

    TraceDebug(m,"dvbtmpeg_m: %d: %s: retval = %d", __LINE__, __FUNCTION__,retval);
    return retval;
}

int CHsvDvbtMpegInstallation_m_Priv::idigscan_GetCurrentPass ( void )
{
    int retval = 1;
    if(StIdle != mDvbtMpegStatus.State)
    {
        retval = 1; /* Only one pass for digital */
    }
    return (retval);
}

int CHsvDvbtMpegInstallation_m_Priv::idigscan_GetNoOfPass(void)
{
    return (1);
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_GetPTCInfo ( HsvInstallationPTC *ptc )
{
    ptc->DecoderType        =   feapi_ChanDecDvbT;
    ptc->SymbolRate         =   0;
    ptc->Frequency          =   (mDvbtMpegStatus.Frequency * 1000)/16;
    ptc->ModulationType     =   mDvbtMpegStatus.ModulationType;
    ptc->CodeRateHigh       =   mDvbtMpegStatus.CodeRateHigh;
    ptc->CodeRateLow        =   mDvbtMpegStatus.CodeRateLow;
    ptc->HierarchyMode      =   HsvHierarchyNone;
    ptc->GuardInterval      =   mDvbtMpegStatus.GuardInterval;
    ptc->TxMode             =   mDvbtMpegStatus.TxMode;
    ptc->IqMode             =   mDvbtMpegStatus.IqMode;
    ptc->ChannelBandwidth   =   mDvbtMpegStatus.ChannelBandwidth;
    ptc->StreamPriority     =   HsvStreamPriorityHigh;
    ptc->ChannelInformation =   mDvbtMpegStatus.ChannelInformation;
    ptc->TimeError          =   mDvbtMpegStatus.TimeError;
    ptc->FrequencyError     =   mDvbtMpegStatus.FrequencyError;
    ptc->FrequencyOffset    =   mDvbtMpegStatus.FrequencyOffset;
    ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
    ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
    ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);

    TraceDebug(m,"dvbtmpeg_m: %d: %s", __LINE__, __FUNCTION__);
}

FResult CHsvDvbtMpegInstallation_m_Priv::idigscan_StoreWeakSignalInstallationChannel()
{
    FResult retval  = err_Ok;
    Nat32 errorcode = TM_OK;
    UNUSED(errorcode);
    if(MANUAL_INSTALL)
    {
        idigacq_AcquireData();

        pgdb_CommitTable(pgdb_GetCurrentTable());
        insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
        insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);

        mDvbtMpegStatus.State = StIdle;
        ASSERT(TM_OK == errorcode);
    }
    else
    {
        retval = err_InstallationCommandNotAllowed;
    }

    TraceDebug(m,"dvbtmpeg_m: %d: %s: retval = %d", __LINE__, __FUNCTION__,retval);
    return retval;
}

/****************************************************************************
 *Function   :
 *Description:
 *Parameters :
 *****************************************************************************/
void CHsvDvbtMpegInstallation_m_Priv::ctrlN_OnEvent( HsvDemux dmx, int eventid )
{
    UNUSED(dmx);
    UNUSED(eventid);
}

void CHsvDvbtMpegInstallation_m_Priv::PlayService(int serviceid)
{
    TraceDebug(m,"dvbtmpeg_m: %s: %d: Service = %d", __FUNCTION__, __LINE__,serviceid);

    mDvbtMpegStatus.PlayStarted = TRUE;

    mctl_Stop(HsvMain);
    mctl_Flush(HsvMain);

    strmfltr_Clear(HsvMain,HsvCurrentProgram,serviceid);
    strmfltr_Set(HsvMain,HsvCurrentProgram,serviceid);

    mctl_Play(HsvMain);
}


void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnStationFound()
{
    if((mDvbtMpegStatus.Active) && (StFeWait == mDvbtMpegStatus.State))
    {
        mDvbtMpegStatus.StationFound = TRUE;
        pmp_PmpSend( mDVBTMpegPump,evStationFound, mDvbtMpegStatus.Frequency);
    }
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnStationNotFound()
{
    TraceDebug(m,"dvbtmpeg_m: %s: %d: ", __FUNCTION__, __LINE__);

    if((mDvbtMpegStatus.Active) && (StFeWait == mDvbtMpegStatus.State))
    {
        mDvbtMpegStatus.StationFound = FALSE;
        pmp_PmpSend( mDVBTMpegPump,evStationNotFound,mDvbtMpegStatus.Frequency);
    }
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnMeasReady( int ssm, Nat32 strength )
{
    UNUSED(ssm);
    UNUSED(strength);
    if(mDvbtMpegStatus.Active)
    {
        pmp_PmpSend(mDVBTMpegPump, evOnMeasReady, (Nat32)NULL);
    }
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnMeasAborted( int ssm )
{
    /* Nothing to be done actually. */
    UNUSED(ssm);
}

void CHsvDvbtMpegInstallation_m_Priv::strapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbtMpegInstallation_m_Priv::strapiN_OnChanged  ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    UNUSED(dest);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
    UNUSED(eventid);

    if(mDvbtMpegStatus.Active)
    {
        switch(spid)
        {
            case HSVSPID(Program, mpeg, pat):
                {
                    if(BACKGROUND_INSTALL)
                    {
                        pmp_PmpSend(mDVBTMpegPump, evPgDatAvailable, mDvbtMpegStatus.Frequency);
                    }
                }
                break;

            default:
                break;
        }
    }
}

void CHsvDvbtMpegInstallation_m_Priv::strapiN_OnRemoved  ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbtMpegInstallation_m_Priv::strapiN_OnCompleted  ( HsvDestination dest, int spid)
{
    if(mDvbtMpegStatus.Active)
    {
        switch(spid)
        {
            case HSVSPID(Program, mpeg, pat):
                {
                    if(BACKGROUND_INSTALL)
                    {
                        /* New PMT has been added. Trigger a background install */
                        pmp_PmpSend(mDVBTMpegPump,evPgDatAvailable,mDvbtMpegStatus.Frequency);
                    }
                    if(MANUAL_INSTALL)
                    {
                        HSVSPTYPE(Program, mpeg, pat) service;

                        strapi_GetByIndex( dest, HSVSPID(Program, mpeg, pat ), 0, (void *)(&service));
                        if(!mDvbtMpegStatus.PlayStarted)
                        {
                            mPATReceived = TRUE;
                            TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
                            PlayService(service.ProgramNumber);
                            pmp_PmpSend(mDVBTMpegPump, evPgDatAvailable, mDvbtMpegStatus.Frequency);

                        }
                    }
                }
                break;

            default:
                break;
        }
    }
}

void CHsvDvbtMpegInstallation_m_Priv::ArmTimerForPAT(void)
{
    mPATReceived = FALSE;
    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    pmp_PmpSendAfter(mDVBTMpegPump, evPATTimeOut , 0, PAT_TIMEOUT);
}

void CHsvDvbtMpegInstallation_m_Priv::HandlePatTimeOut(Nat32 param)
{
    UNUSED(param);
    if((mPATReceived == FALSE) && (mDvbtMpegStatus.Active) && (StDmxWait == mDvbtMpegStatus.State))
    {
        mPATReceived = TRUE;
        TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
        pmp_PmpSend( mDVBTMpegPump, evPgDatAvailable, mDvbtMpegStatus.Frequency);
    }
}

#ifndef __cplusplus

void CHsvDvbtMpegInstallation_m_Priv::idigscan_SetChanBandwidth(HsvChanBandwidth BandWidth)
{
    ASSERT(!"This function call is not supported");
    UNUSED(BandWidth);
}

HsvChanBandwidth CHsvDvbtMpegInstallation_m_Priv::idigscan_GetChanBandwidth(void)
{
    tmFe_ChanBandwidth_t param1;
    Nat32 errorcode = TM_OK;
    Bool ChanDecDvbTHandle = TRUE;

    if (ChanDecDvbTHandle)
    {
        feapi_GetActualChanBandwidth (WINDOWID, &param1, &errorcode);
        ASSERT(TM_OK  ==  errorcode);
        mDvbtMpegStatus.ChannelBandwidth = param1;//(Nat8 )ConvertFromPlatformChanBandwidth(param1);
    }
    return  mDvbtMpegStatus.ChannelBandwidth;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_SetCodeRate(HsvCodeRate  hicoderate, HsvCodeRate  lowcoderate)
{
    ASSERT(!"This function call is not supported");
    UNUSED(hicoderate);
    UNUSED(lowcoderate);
}

HsvCodeRate CHsvDvbtMpegInstallation_m_Priv::idigscan_GetCodeRate(HsvStreamPriority prio)
{
    UNUSED(prio);
    return HsvCodeRateAuto;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_SetGuardInterval(HsvGuardInterval grdintvl)
{
    ASSERT(!"This function call is not supported");
    UNUSED(grdintvl);
}

HsvGuardInterval CHsvDvbtMpegInstallation_m_Priv::idigscan_GetGuardInterval(void)
{
    return HsvGuardIntervalAuto;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_SetTxMode(HsvTxMode txmode)
{
    ASSERT(!"This function call is not supported");
    UNUSED(txmode);
}

HsvTxMode CHsvDvbtMpegInstallation_m_Priv::idigscan_GetTxMode(void)
{
    return HsvTxModeAuto;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_SetFrequencyOffset(HsvFrequencyOffset  freqoffset)
{
    ASSERT(!"This function call is not supported");
    UNUSED(freqoffset);
}

HsvFrequencyOffset CHsvDvbtMpegInstallation_m_Priv::idigscan_GetFrequencyOffset(void)
{
    return HsvOffsetNone;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_SetConstellation(HsvConstellation  con)
{
    ASSERT(!"This function call is not supported");
    UNUSED(con);
}

HsvConstellation CHsvDvbtMpegInstallation_m_Priv::idigscan_GetConstellation(void)
{
    tmFe_Constellation_t param1;
    Nat32 errorcode = TM_OK;
    Bool ChanDecHandle = TRUE;

    if (ChanDecHandle)
    {
        feapi_GetActualConstellation(WINDOWID,feapi_ChanDecDvbT, &param1, &errorcode);
        ASSERT(TM_OK  ==  errorcode);
        mDvbtMpegStatus.ModulationType = param1; //(Nat8 )ConvertFromPlatformConstellation(param1);
    }
    return mDvbtMpegStatus.ModulationType;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_SetIqMode(HsvIqMode  iq)
{
    ASSERT(!"This function call is not supported");
    UNUSED(iq);
}

HsvIqMode CHsvDvbtMpegInstallation_m_Priv::idigscan_GetIqMode(void)
{
    return HsvIqModeNormal;
}

#endif


void CHsvDvbtMpegInstallation_m_Priv::ena_Enable(void)
{
    mDvbtMpegStatus.Active = TRUE;
}

void CHsvDvbtMpegInstallation_m_Priv::ena_Disable(void)
{
    mDvbtMpegStatus.Active = FALSE;
}

HsvConstellation CHsvDvbtMpegInstallation_m_Priv::ConvertFromPlatformConstellation(tmFe_Constellation_t inval)
{
    HsvConstellation outval = (HsvConstellation)0;
    switch(inval)
    {
#define HSVCONSTELLATION(a)  case (tmFe_##a): \
        outval  =   Hsv##a;    \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

        default:
            break;
    }
    return outval;
}

HsvCodeRate CHsvDvbtMpegInstallation_m_Priv::ConvertFromPlatformCodeRate(tmFe_CodeRate_t inval)
{
    HsvCodeRate outval = (HsvCodeRate)0;
    switch(inval)
    {
#define HSVCODERATE(a)  case (tmFe_##a): \
        outval  =   Hsv##a;    \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

        default:
            break;
    }
    return outval;
}

HsvHierarchyMode CHsvDvbtMpegInstallation_m_Priv::ConvertFromPlatformHierarchyMode(tmFe_HierarchyMode_t inval)
{
    HsvHierarchyMode outval = (HsvHierarchyMode)0;
    switch(inval)
    {
#define HSVHIERARCHYMODE(a)  case (tmFe_##a): \
        outval  =   Hsv##a;    \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

        default:
            break;
    }
    return outval;
}

HsvGuardInterval CHsvDvbtMpegInstallation_m_Priv::ConvertFromPlatformGuardInterval(tmFe_GuardInterval_t inval)
{
    HsvGuardInterval outval = (HsvGuardInterval)0;
    switch(inval)
    {
#define HSVGUARDINTERVAL(a)  case (tmFe_##a): \
        outval  =   Hsv##a;    \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

        default:
            break;
    }
    return outval;
}

HsvTxMode CHsvDvbtMpegInstallation_m_Priv::ConvertFromPlatformTxMode(tmFe_TxMode_t inval)
{
    HsvTxMode outval = (HsvTxMode)0;
    switch(inval)
    {
#define HSVTXMODE(a)  case (tmFe_##a): \
        outval  =   Hsv##a;    \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

        default:
            break;
    }
    return outval;
}

HsvChanBandwidth CHsvDvbtMpegInstallation_m_Priv::ConvertFromPlatformChanBandwidth(tmFe_ChanBandwidth_t inval)
{
    HsvChanBandwidth outval = (HsvChanBandwidth)0;
    switch(inval)
    {
#define HSVCHANBANDWIDTH(a)  case (tmFe_##a): \
        outval  =   Hsv##a;    \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

        default:
            break;
    }
    return outval;
}

HsvFrequencyOffset CHsvDvbtMpegInstallation_m_Priv::ConvertFromPlatformFrequencyOffset(tmFe_FrequencyOffset_t inval)
{
    HsvFrequencyOffset outval = (HsvFrequencyOffset)0;
    switch(inval)
    {
#define HSVFREQUENCYOFFSET(a)  case (tmFe_##a): \
        outval  =   Hsv##a;    \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

        default:
            break;
    }
    return outval;
}

HsvStreamPriority CHsvDvbtMpegInstallation_m_Priv::ConvertFromPlatformStreamPriority(tmFe_StreamPriority_t inval)
{
    HsvStreamPriority outval = HsvStreamPriorityHigh;

    switch(inval)
    {
        case tmFe_StreamPriorityHigh:
            outval = HsvStreamPriorityHigh;
            break;

        case tmFe_StreamPriorityLow:
            outval = HsvStreamPriorityLow;
            break;

        default:
            break;
    }
    return outval;
}

void CHsvDvbtMpegInstallation_m_Priv::SetStreamPriority(HsvStreamPriority prio)
{
    Nat32 errorcode = TM_OK;

    tmFe_StreamPriority_t  plfStreamPrio = ConvertToPlatformStreamPriority(prio);    
    feapi_SetStreamPriority(WINDOWID, plfStreamPrio, &errorcode);

    ASSERT(TM_OK == errorcode);
}

tmFe_StreamPriority_t CHsvDvbtMpegInstallation_m_Priv::ConvertToPlatformStreamPriority(HsvStreamPriority inval)
{

    tmFe_StreamPriority_t outval = tmFe_StreamPriorityHigh;

    switch(inval)
    {

        case HsvStreamPriorityHigh:
            outval = tmFe_StreamPriorityHigh;
            break;

        case HsvStreamPriorityLow:
            outval = tmFe_StreamPriorityLow;
            break;

        default:
            break;
    }
    return outval;
}

int CHsvDvbtMpegInstallation_m_Priv::mGetMaxFrequency(HsvInstallationSpectrum *Spectrum)
{
    int i = 0, retval  = 0;

    while((Spectrum[i].EndFrequency) != INVALID_FREQUENCY)
    {
        if(retval < Spectrum[i].EndFrequency)
        {
            retval = Spectrum[i].EndFrequency;
        }
        i++;
    }

    return retval;
}


int CHsvDvbtMpegInstallation_m_Priv::mGetCorrectedFrequency(int Frequency, int Country)
{
    Bool FrequencyCorrected = FALSE;
    int i = 0, MinFreq, MaxFreq, NoofMatches = 0, FrequencyDiff = 0, UserFrequency, CorrectedFrequency, centrefrequency;

    MinFreq = MaxFreq = INVALID_FREQUENCY;
    UserFrequency = CorrectedFrequency = Frequency;
    HsvInstallationSpectrum *Spectrum = (HsvInstallationSpectrum *)((ANTENNA_MEDIUM)?AntennaSpectrum[Country]: CableSpectrum);

    while( (MinFreq = Spectrum[i].StartFrequency)!= INVALID_FREQUENCY )
    {
        MaxFreq    =   Spectrum[i].EndFrequency;
        CorrectedFrequency = UserFrequency;
        if ( MinFreq <= UserFrequency )
        {
            if( MaxFreq >= UserFrequency)
            {
                int bandbw      =   mConvertBandwidthToValue(Spectrum[i].Bandwidth) << 4;
                if((UserFrequency - MinFreq) % bandbw  > bandbw/2)
                {
                    CorrectedFrequency = UserFrequency + bandbw;
                }
                CorrectedFrequency = CorrectedFrequency - (UserFrequency-MinFreq) % bandbw;
                centrefrequency = UserFrequency + ((MaxFreq- UserFrequency) % bandbw) + bandbw/2;

                if ((centrefrequency + bandbw/2 == MaxFreq) && ((centrefrequency - bandbw) == MinFreq))
                {
                    CorrectedFrequency =  centrefrequency;
                }

                FrequencyCorrected = TRUE;
                NoofMatches++;
                if(NoofMatches == 1)
                {
                    FrequencyDiff = GET_ABSOLUTE_VAL (UserFrequency - CorrectedFrequency);
                    Frequency = CorrectedFrequency;
                }
                else
                {
                    if(FrequencyDiff > GET_ABSOLUTE_VAL(UserFrequency - CorrectedFrequency))
                    {
                        FrequencyDiff = GET_ABSOLUTE_VAL(UserFrequency - CorrectedFrequency);
                        Frequency = CorrectedFrequency;
                    }
                }
            }
        }
        else
        {   /* Outside the country band - but there may be valid bands after it */
            break;
        }
        i++;
    }
    if(!FrequencyCorrected)
    {
        if( Spectrum[i].StartFrequency == INVALID_FREQUENCY)
        {
            Frequency = Spectrum[i - 1].EndFrequency;
        }
        else
        {
            Frequency = Spectrum[i].StartFrequency;
        }
    }
    TraceDebug(m,"%s %d Frequency %d", __FUNCTION__, __LINE__, Frequency);
    return Frequency;
}

int CHsvDvbtMpegInstallation_m_Priv::mConvertBandwidthToValue(tmFe_ChanBandwidth_t Bandwidth)
{
    int retval = 8;
    switch(Bandwidth)
    {
        case tmFe_ChanBandwidth6MHz:
            retval = 6;
            break;
        case tmFe_ChanBandwidth7MHz:
            retval = 7;
            break;
        case tmFe_ChanBandwidth8MHz:
            retval = 8;
            break;
        default:
            break;
    }
    return retval;
}

/* Interfaces from IHsvdigitalscan.id */


FResult CHsvDvbtMpegInstallation_m_Priv::idigscan_StopInstallation(void ) 
{
	return 0;
}




int CHsvDvbtMpegInstallation_m_Priv::idigscan_GetNumberOfDigitalChannelsFound() 
{
	return 0;
}

int CHsvDvbtMpegInstallation_m_Priv::idigscan_GetNumberOfDigitalChannelsRemoved() 
{
	return 0;
}

int CHsvDvbtMpegInstallation_m_Priv::idigscan_GetTargetNitType(Nat16* NetworkId) 
{
	return NULL;
}

int CHsvDvbtMpegInstallation_m_Priv::idigscan_GetCurrentState() 
{
	return 0;
}

int CHsvDvbtMpegInstallation_m_Priv::idigscan_GetSDTType() 
{
	return 0;
}

Bool CHsvDvbtMpegInstallation_m_Priv::idigscan_GetAltTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

Bool CHsvDvbtMpegInstallation_m_Priv::idigscan_GetCurTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

HsvStreamPriority CHsvDvbtMpegInstallation_m_Priv::idigscan_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_SetStreamPriority (HsvStreamPriority prio) 
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_SyncComplete(void)     
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_ClearCache(void) 
{
	return;
}

int CHsvDvbtMpegInstallation_m_Priv::idigscan_GetPLPIds(int *PLPIds) 
{
	return NULL;
}

HsvHierarchyMode CHsvDvbtMpegInstallation_m_Priv::idigscan_GetHierarchyMode(void) 
{
	return (HsvHierarchyMode)0;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid) 
{
	return;
}

int CHsvDvbtMpegInstallation_m_Priv::idigscan_ZiggoGetSDTType(Nat16 Frequency) 
{
	return 0;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return;
}

Bool CHsvDvbtMpegInstallation_m_Priv::idigscan_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}

void CHsvDvbtMpegInstallation_m_Priv::idigscan_ClearPersistent() 
{
	return;
}


void CHsvDvbtMpegInstallation_m_Priv::idigscan_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


/* Interfaces from IHsvFrontEndApiNotify.id */

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnSearchStateChanged (tmFe_SearchState_t state)   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnSearchInProgress (  tmFe_SearchState_t state  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnTvSystemDetected (  tmFe_TvSystem_t tvSystem  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnAfcFreqChanged (  Nat32 freq  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnAfcLimitReached ( Nat32 freq  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnAfcModeChanged (  void  )   
{
	return;
}


void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnConstellationDetected (  tmFe_Constellation_t  ellation  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnIqModeDetected (  tmFe_IqMode_t mode  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnCodeRateDetected (  tmFe_CodeRate_t highPrioRate ,  tmFe_CodeRate_t lowPrioRate  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnHierarchyModeDetected (  tmFe_HierarchyMode_t mode  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnGuardIntervalDetected (  tmFe_GuardInterval_t interval  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnTxModeDetected (  tmFe_TxMode_t mode  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnChanBandwidthDetected (  tmFe_ChanBandwidth_t bandwith  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnCarrierPresentChanged (  Bool carrier  )   
{
	return;
}

void CHsvDvbtMpegInstallation_m_Priv::feapiN_OnBerThresholdCrossed (  Nat32 ber ,  Nat32 berThreshold  )   
{
	return;
}

