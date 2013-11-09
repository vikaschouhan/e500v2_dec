#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>

//////////////////////////////////////////////////////////////////////////////////////
// Copyright Vikas Chouhan (presentisgood@gmail.com) 2013/2014.
//
//
//  This library is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License Version 2 as
//  published by the Free Software Foundation.
//
//  It is distributed in the hope that it will be useful, but WITHOUT
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
//  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
//  License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this file; see the file COPYING.  If not, write to the
//  Free Software Foundation, 51 Franklin Street - Fifth Floor, Boston,
//  MA 02110-1301, USA.
//
//
//
// NOTE : This code needs to be compiled with gcc using stdc++0x standard.
////////////////////////////////////////////////////////////////////////////////////////

#define PPC_SPE

namespace ppcbooke{
    namespace ppcbooke_dis{
        namespace details{

            // utility functions for converting integer to hex and decimal string forms
            // TSH -> convert to string in hex form
            // TS  -> simply convert to string
            // TIS -> cast to some other data type & then convert to integer string
            std::string                           TSH(uint32_t v) { std::stringstream t; t << std::hex << v; return "0x" + t.str(); }
            std::string                           TS(uint32_t v)  { std::stringstream t; t << v; return t.str(); }
            template<typename T>  std::string     TIS(uint32_t v) { std::stringstream t; t << static_cast<T>(v); return t.str(); }

            //////////////////////////////////////////////////////////////////////////
            // powerpc opcodes (e500v2 booke only)
            //////////////////////////////////////////////////////////////////////////
#if 0
            enum ppc_op {
                // A
                ppc_op_add,           ppc_op_add_dot,        ppc_op_addc,          ppc_op_addc_dot,
                ppc_op_addco,         ppc_op_addco_dot,      ppc_op_adde,          ppc_op_adde_dot,
                ppc_op_addeo,         ppc_op_addeo_dot,      ppc_op_addi,          ppc_op_addic,
                ppc_op_addic_dot,     ppc_op_addis,          ppc_op_addme,         ppc_op_addme_dot,
                ppc_op_addmeo,        ppc_op_addmeo_dot,     ppc_op_addo,          ppc_op_addo_dot,
                ppc_op_addze,         ppc_op_addze_dot,      ppc_op_addzeo,        ppc_op_addzeo_dot,
                ppc_op_and,           ppc_op_and_dot,        ppc_op_andc,          ppc_op_andc_dot,
                ppc_op_andi_dot,      ppc_op_andis_dot,
                // B
                ppc_op_b,             ppc_op_ba,
                ppc_op_bbelr,         ppc_op_bblels,         ppc_op_bc,            ppc_op_bca,
                ppc_op_bcctr,         ppc_op_bcctrl,         ppc_op_bcl,           ppc_op_bcla,
                ppc_op_bclr,          ppc_op_bclrl,          ppc_op_bl,            ppc_op_bla,
                ppc_op_brinc,
                // C
                ppc_op_cmp,           ppc_op_cmpi,           ppc_op_cmpl,          ppc_op_cmpli,
                ppc_op_cntlzw,        ppc_op_cntlzw_dot,     ppc_op_crand,         ppc_op_crandc,
                ppc_op_creqv,         ppc_op_crnand,         ppc_op_crnor,         ppc_op_cror, 
                ppc_op_crorc,         ppc_op_crxor,
                // D
                ppc_op_dcba,          ppc_op_dcbf,           ppc_op_dcbi,          ppc_op_dcblc,
                ppc_op_dcbst,         ppc_op_dcbt,           ppc_op_dcbtls,        ppc_op_dcbtst,
                ppc_op_dcbtstls,      ppc_op_dcbz,           ppc_op_divw,          ppc_op_divw_dot,
                ppc_op_divwo,         ppc_op_divwo_dot,      ppc_op_divwu,         ppc_op_divwu_dot,
                ppc_op_divwuo,        ppc_op_divwuo_dot,
                // E
                ppc_op_efdabs,        ppc_op_efdadd,         ppc_op_efdcfs,        ppc_op_efdcfsf,
                ppc_op_efdcfsi,       ppc_op_efdcfuf,        ppc_op_efdcfui,       ppc_op_efdcmpeq,
                ppc_op_efdcmpgt,      ppc_op_efdcmplt,       ppc_op_efdctsf,       ppc_op_efdctsi,
                ppc_op_efdctsiz,      ppc_op_efdctuf,        ppc_op_efdctui,       ppc_op_efdctuiz,
                ppc_op_efddiv,        ppc_op_efdmul,         ppc_op_efdnabs,       ppc_op_efdneg,
                ppc_op_efdsub,        ppc_op_efdtsteq,       ppc_op_efdtstgt,      ppc_op_efdtstlt,
                ppc_op_efsabs,        ppc_op_efsadd,         ppc_op_efscfd,        ppc_op_efscfsf, 
                ppc_op_efscfsi,       ppc_op_efscfuf,        ppc_op_efscfui,       ppc_op_efscmpeq,
                ppc_op_efscmpgt,      ppc_op_efscmplt,       ppc_op_efsctsf,       ppc_op_efsctsi, 
                ppc_op_efsctsiz,      ppc_op_efsctuf,        ppc_op_efsctui,       ppc_op_efsctuiz,
                ppc_op_efsdiv,        ppc_op_efsmul,         ppc_op_efsnabs,       ppc_op_efsneg,
                ppc_op_efssub,        ppc_op_efststeq,       ppc_op_efststgt,      ppc_op_efststlt,
                ppc_op_eqv,           ppc_op_eqv_dot,        ppc_op_evabs,         ppc_op_evaddiw,
                ppc_op_evaddsmiaaw,   ppc_op_evaddssiaaw,    ppc_op_evaddumiaaw,   ppc_op_evaddusiaaw, 
                ppc_op_evaddw,        ppc_op_evand,          ppc_op_evandc,        ppc_op_evcmpeq,
                ppc_op_evcmpgts,      ppc_op_evcmpgtu,       ppc_op_evcmplts,      ppc_op_evcmpltu,
                ppc_op_evcntlsw,      ppc_op_evcntlzw,       ppc_op_evdivws,       ppc_op_evdivwu,
                ppc_op_eveqv,         ppc_op_evextsb,        ppc_op_evextsh,       ppc_op_evfsabs,
                ppc_op_evfsadd,       ppc_op_evfscfsf,       ppc_op_evfscfsi,      ppc_op_evfscfuf,
                ppc_op_evfscfui,      ppc_op_evfscmpeq,      ppc_op_evfscmpgt,     ppc_op_evfscmplt,
                ppc_op_evfsctsf,      ppc_op_evfsctsi,       ppc_op_evfsctsiz,     ppc_op_evfsctuf,
                ppc_op_evfsctui,      ppc_op_evfsctuiz,      ppc_op_evfsdiv,       ppc_op_evfsmul,
                ppc_op_evfsnabs,      ppc_op_evfsneg,        ppc_op_evfssub,       ppc_op_evfststeq,
                ppc_op_evfststgt,     ppc_op_evfststlt,      ppc_op_evldd,         ppc_op_evlddx,
                ppc_op_evldh,         ppc_op_evldhx,         ppc_op_evldw,         ppc_op_evldwx,
                ppc_op_evlhhesplat,   ppc_op_evlhhesplatx,   ppc_op_evlhhossplat,  ppc_op_evlhhossplatx,
                ppc_op_evlhhousplat,  ppc_op_evlhhousplatx,  ppc_op_evlwhe,        ppc_op_evlwhex,
                ppc_op_evlwhos,       ppc_op_evlwhosx,       ppc_op_evlwhou,       ppc_op_evlwhoux,
                ppc_op_evlwhsplat,    ppc_op_evlwhsplatx,    ppc_op_evlwwsplat,    ppc_op_evlwwsplatx,
                ppc_op_evmergehi,     ppc_op_evmergehilo,    ppc_op_evmergelo,     ppc_op_evmergelohi,
                ppc_op_evmhegsmfaa,   ppc_op_evmhegsmfan,    ppc_op_evmhegsmiaa,   ppc_op_evmhegsmian,
                ppc_op_evmhegumiaa,   ppc_op_evmhegumian,    ppc_op_evmhesmf,      ppc_op_evmhesmfa,
                ppc_op_evmhesmfaaw,   ppc_op_evmhesmfanw,    ppc_op_evmhesmi,      ppc_op_evmhesmia,
                ppc_op_evmhesmiaaw,   ppc_op_evmhesmianw,    ppc_op_evmhessf,      ppc_op_evmhessfa,
                ppc_op_evmhessfaaw,   ppc_op_evmhessfanw,    ppc_op_evmhessiaaw,   ppc_op_evmhessianw,
                ppc_op_evmheumi,      ppc_op_evmheumia,      ppc_op_evmheumiaaw,   ppc_op_evmheumianw,
                ppc_op_evmheusiaaw,   ppc_op_evmheusianw,    ppc_op_evmhogsmfaa,   ppc_op_evmhogsmfan,
                ppc_op_evmhogsmiaa,   ppc_op_evmhogsmian,    ppc_op_evmhogumiaa,   ppc_op_evmhogumian,
                ppc_op_evmhosmf,      ppc_op_evmhosmfa,      ppc_op_evmhosmfaaw,   ppc_op_evmhosmfanw,
                ppc_op_evmhosmi,      ppc_op_evmhosmia,      ppc_op_evmhosmiaaw,   ppc_op_evmhosmianw,
                ppc_op_evmhossf,      ppc_op_evmhossfa,      ppc_op_evmhossfaaw,   ppc_op_evmhossfanw,
                ppc_op_evmhossiaaw,   ppc_op_evmhossianw,    ppc_op_evmhoumi,      ppc_op_evmhoumia,
                ppc_op_evmhoumiaaw,   ppc_op_evmhoumianw,    ppc_op_evmhousiaaw,   ppc_op_evmhousianw,
                ppc_op_evmra,         ppc_op_evmwhsmf,       ppc_op_evmwhsmfa,     ppc_op_evmwhsmi,
                ppc_op_evmwhsmia,     ppc_op_evmwhssf,       ppc_op_evmwhssfa,     ppc_op_evmwhumi,
                ppc_op_evmwhumia,     ppc_op_evmwhusiaaw,    ppc_op_evmwhusianw,   ppc_op_evmwlumi,
                ppc_op_evmwlumia,     ppc_op_evmwlumiaaw,    ppc_op_evmwlumianw,   ppc_op_evmwlusiaaw,
                ppc_op_evmwlusianw,   ppc_op_evmwsmf,        ppc_op_evmwsmfa,      ppc_op_evmwsmfaa,
                ppc_op_evmwsmfan,     ppc_op_evmwsmi,        ppc_op_evmwsmia,      ppc_op_evmwsmiaa,
                ppc_op_evmwsmian,     ppc_op_evmwssf,        ppc_op_evmwssfa,      ppc_op_evmwssfaa,
                ppc_op_evmwssfan,     ppc_op_evmwumi,        ppc_op_evmwumia,      ppc_op_evmwumiaa,
                ppc_op_evmwumian,     ppc_op_evnand,         ppc_op_evneg,         ppc_op_evnor,
                ppc_op_evor,          ppc_op_evorc,          ppc_op_evrlw,         ppc_op_evrlwi,
                ppc_op_evrndw,        ppc_op_evsel,          ppc_op_evslw,         ppc_op_evslwi,
                ppc_op_evsplatfi,     ppc_op_evsplati,       ppc_op_evsrwis,       ppc_op_evsrwiu,
                ppc_op_evsrws,        ppc_op_evsrwu,         ppc_op_evstdd,        ppc_op_evstddx,
                ppc_op_evstdh,        ppc_op_evstdhx,        ppc_op_evstdw,        ppc_op_evstdwx,
                ppc_op_evstwhe,       ppc_op_evstwhex,       ppc_op_evstwho,       ppc_op_evstwhox,
                ppc_op_evstwwe,       ppc_op_evstwwex,       ppc_op_evstwwo,       ppc_op_evstwwox,
                ppc_op_evsubfsmiaaw,  ppc_op_evsubfssiaaw,   ppc_op_evsubfumiaaw,  ppc_op_evsubfusiaaw,
                ppc_op_evsubfw,       ppc_op_evsubifw,       ppc_op_evxor,         ppc_op_extsb,
                ppc_op_extsb_dot,     ppc_op_extsh,          ppc_op_extsh_dot,
                // I 
                ppc_op_icbi,          ppc_op_icblc,          ppc_op_icbt,          ppc_op_icbtls,
                ppc_op_isel,          ppc_op_isync,
                // L 
                ppc_op_lbz,           ppc_op_lbzu,           ppc_op_lbzux,         ppc_op_lbzx,
                ppc_op_lha,           ppc_op_lhau,           ppc_op_lhaux,         ppc_op_lhax,
                ppc_op_lhbrx,         ppc_op_lhz,            ppc_op_lhzu,          ppc_op_lhzux,
                ppc_op_lhzx,          ppc_op_lmw,            ppc_op_lwarx,         ppc_op_lwbrx,
                ppc_op_lwz,           ppc_op_lwzu,           ppc_op_lwzux,         ppc_op_lwzx,
                // M 
                ppc_op_mbar,          ppc_op_mcrf,           ppc_op_mcrxr,         ppc_op_mfcr,
                ppc_op_mfmsr,         ppc_op_mfpmr,          ppc_op_mfspr,         ppc_op_msync,
                ppc_op_mtcrf,         ppc_op_mtmsr,          ppc_op_mtpmr,         ppc_op_mtspr,
                ppc_op_mulhw,         ppc_op_mulhw_dot,      ppc_op_mulhwu,        ppc_op_mulhwu_dot,
                ppc_op_mulli,         ppc_op_mullw,          ppc_op_mullw_dot,     ppc_op_mullwo,
                ppc_op_mullwo_dot,
                // N 
                ppc_op_nand,          ppc_op_nand_dot,       ppc_op_neg,           ppc_op_neg_dot,
                ppc_op_nego,          ppc_op_nego_dot,       ppc_op_nor,           ppc_op_nor_dot,
                // O 
                ppc_op_or,            ppc_op_or_dot,         ppc_op_orc,           ppc_op_orc_dot,
                ppc_op_ori,           ppc_op_oris,
                // R 
                ppc_op_rfci,          ppc_op_rfi,            ppc_op_rfmci,         ppc_op_rlwimi,
                ppc_op_rlwimi_dot,    ppc_op_rlwinm,         ppc_op_rlwinm_dot,    ppc_op_rlwnm,
                ppc_op_rlwnm_dot,
                // S 
                ppc_op_sc,            ppc_op_slw,            ppc_op_slw_dot,       ppc_op_sraw,
                ppc_op_sraw_dot,      ppc_op_srawi,          ppc_op_srawi_dot,     ppc_op_srw,
                ppc_op_srw_dot,       ppc_op_stb,            ppc_op_stbu,          ppc_op_stbux,
                ppc_op_stbx,          ppc_op_sth,            ppc_op_sthbrx,        ppc_op_sthu,
                ppc_op_sthux,         ppc_op_sthx,           ppc_op_stmw,          ppc_op_stw,
                ppc_op_stwbrx,        ppc_op_stwcx_dot,      ppc_op_stwu,          ppc_op_stwux,
                ppc_op_stwx,          ppc_op_subf,           ppc_op_subf_dot,      ppc_op_subfc,
                ppc_op_subfc_dot,     ppc_op_subfco,         ppc_op_subfco_dot,    ppc_op_subfe,
                ppc_op_subfe_dot,     ppc_op_subfeo,         ppc_op_subfeo_dot,    ppc_op_subfic,
                ppc_op_subfme,        ppc_op_subfme_dot,     ppc_op_subfmeo,       ppc_op_subfmeo_dot,
                ppc_op_subfo,         ppc_op_subfo_dot,      ppc_op_subfze,        ppc_op_subfze_dot,
                ppc_op_subfzeo,       ppc_op_subfzeo_dot,
                // T 
                ppc_op_tlbivax,       ppc_op_tlbre,          ppc_op_tlbsx,         ppc_op_tlbsync,
                ppc_op_tlbwe,         ppc_op_tw,             ppc_op_twi,
                // W
                ppc_op_wrtee,         ppc_op_wrteei,
                // X
                ppc_op_xor,           ppc_op_xor_dot,        ppc_op_xori,          ppc_op_xoris,
                // CNT
                ppc_op_total
            };
#endif

            //////////////////////////////////////////////////////////////////////////
            // ppc opcode groups
            //////////////////////////////////////////////////////////////////////////
            // form types
            enum ppc_op_form {
                ppc_op_form_i = 1,
                ppc_op_form_b,
                ppc_op_form_sc,
                ppc_op_form_d,
                ppc_op_form_x,
                ppc_op_form_xl,
                ppc_op_form_xfx,
                ppc_op_form_xo,
                ppc_op_form_a,
                ppc_op_form_m,
                ppc_op_form_evx,
                ppc_op_form_evs
            };

            // subform types
            enum ppc_op_subform {
                // i form
                ppc_op_subform_i_li                   = (ppc_op_form_i   << 16) | 0x1,
                // b form
                ppc_op_subform_b_bo_bi_bd             = (ppc_op_form_b   << 16) | 0x1,
                // sc form
                ppc_op_subform_sc                     = (ppc_op_form_sc  << 16) | 0x1,
                ppc_op_subform_sc_lev                 = (ppc_op_form_sc  << 16) | 0x2,
                // d form
                ppc_op_subform_d_rt_ra_d              = (ppc_op_form_d   << 16) | 0x1,
                ppc_op_subform_d_rt_ra_si             = (ppc_op_form_d   << 16) | 0x2,
                ppc_op_subform_d_rs_ra_d              = (ppc_op_form_d   << 16) | 0x3,
                ppc_op_subform_d_rs_ra_ui             = (ppc_op_form_d   << 16) | 0x4,
                ppc_op_subform_d_bf_l_ra_si           = (ppc_op_form_d   << 16) | 0x5,
                ppc_op_subform_d_bf_l_ra_ui           = (ppc_op_form_d   << 16) | 0x6,
                ppc_op_subform_d_to_ra_si             = (ppc_op_form_d   << 16) | 0x7,
                // x form
                ppc_op_subform_x_rt_ra                = (ppc_op_form_x   << 16) | 0x1,
                ppc_op_subform_x_rt_ra_rb             = (ppc_op_form_x   << 16) | 0x2,
                ppc_op_subform_x_rt_ra_nb             = (ppc_op_form_x   << 16) | 0x3,
                ppc_op_subform_x_rt_sr                = (ppc_op_form_x   << 16) | 0x4,
                ppc_op_subform_x_rt_rb                = (ppc_op_form_x   << 16) | 0x5,
                ppc_op_subform_x_rt                   = (ppc_op_form_x   << 16) | 0x6,
                ppc_op_subform_x_rs_ra_rb             = (ppc_op_form_x   << 16) | 0x7,
                ppc_op_subform_x_rs_ra_nb             = (ppc_op_form_x   << 16) | 0x8,
                ppc_op_subform_x_rs_ra_sh             = (ppc_op_form_x   << 16) | 0x9,
                ppc_op_subform_x_rs_ra                = (ppc_op_form_x   << 16) | 0xa,
                ppc_op_subform_x_rs_sr                = (ppc_op_form_x   << 16) | 0xb,
                ppc_op_subform_x_rs_rb                = (ppc_op_form_x   << 16) | 0xc,
                ppc_op_subform_x_rs                   = (ppc_op_form_x   << 16) | 0xd,
                ppc_op_subform_x_rs_l                 = (ppc_op_form_x   << 16) | 0xe,
                ppc_op_subform_x_th_ra_rb             = (ppc_op_form_x   << 16) | 0xf,
                ppc_op_subform_x_bf_l_ra_rb           = (ppc_op_form_x   << 16) | 0x10,
                ppc_op_subform_x_bf_bfa               = (ppc_op_form_x   << 16) | 0x11,
                ppc_op_subform_x_bf                   = (ppc_op_form_x   << 16) | 0x12,
                ppc_op_subform_x_ct                   = (ppc_op_form_x   << 16) | 0x14,
                ppc_op_subform_x_ct_ra_rb             = (ppc_op_form_x   << 16) | 0x15,
                ppc_op_subform_x_l_ra_rb              = (ppc_op_form_x   << 16) | 0x16,
                ppc_op_subform_x_l_rb                 = (ppc_op_form_x   << 16) | 0x17,
                ppc_op_subform_x_l                    = (ppc_op_form_x   << 16) | 0x18,
                ppc_op_subform_x_to_ra_rb             = (ppc_op_form_x   << 16) | 0x19,
                ppc_op_subform_x_bt                   = (ppc_op_form_x   << 16) | 0x1a,
                ppc_op_subform_x_ra_rb                = (ppc_op_form_x   << 16) | 0x1b,
                ppc_op_subform_x_rb                   = (ppc_op_form_x   << 16) | 0x1c,
                ppc_op_subform_x_e                    = (ppc_op_form_x   << 16) | 0x1d,
                ppc_op_subform_x_ih                   = (ppc_op_form_x   << 16) | 0x1e,
                ppc_op_subform_x_t_ra_rb              = (ppc_op_form_x   << 16) | 0x1f,
                ppc_op_subform_x_mo                   = (ppc_op_form_x   << 16) | 0x20,
                ppc_op_subform_x                      = (ppc_op_form_x   << 16) | 0x21,
                // xl form
                ppc_op_subform_xl_bt_ba_bb            = (ppc_op_form_xl  << 16) | 0x1,
                ppc_op_subform_xl_bo_bi_bh            = (ppc_op_form_xl  << 16) | 0x2,
                ppc_op_subform_xl_bf_bfa              = (ppc_op_form_xl  << 16) | 0x3,
                ppc_op_subform_xl                     = (ppc_op_form_xl  << 16) | 0x4,
                // xfx form
                ppc_op_subform_xfx_rt_spr             = (ppc_op_form_xfx << 16) | 0x1,
                ppc_op_subform_xfx_rt                 = (ppc_op_form_xfx << 16) | 0x2,
                ppc_op_subform_xfx_rt_pmr             = (ppc_op_form_xfx << 16) | 0x3,
                ppc_op_subform_xfx_rs_fxm             = (ppc_op_form_xfx << 16) | 0x4,
                ppc_op_subform_xfx_rs_spr             = (ppc_op_form_xfx << 16) | 0x5,
                ppc_op_subform_xfx_rs_pmr             = (ppc_op_form_xfx << 16) | 0x6,
                // xo form
                ppc_op_subform_xo_rt_ra_rb            = (ppc_op_form_xo  << 16) | 0x1,
                ppc_op_subform_xo_rt_ra               = (ppc_op_form_xo  << 16) | 0x2,
                //a form
                ppc_op_subform_a_rt_ra_rb_bc          = (ppc_op_form_a   << 16) | 0x1,
                // m form
                ppc_op_subform_m_rs_ra_rb_mb_me       = (ppc_op_form_m   << 16) | 0x1,
                ppc_op_subform_m_rs_ra_sh_mb_me       = (ppc_op_form_m   << 16) | 0x2,
                // evx form
                ppc_op_subform_evx_rs_ra_rb           = (ppc_op_form_evx << 16) | 0x1,
                ppc_op_subform_evx_rs_ra_ui           = (ppc_op_form_evx << 16) | 0x2,
                ppc_op_subform_evx_rt_rb              = (ppc_op_form_evx << 16) | 0x3,
                ppc_op_subform_evx_rt_ra_rb           = (ppc_op_form_evx << 16) | 0x4,
                ppc_op_subform_evx_rt_ra              = (ppc_op_form_evx << 16) | 0x5,
                ppc_op_subform_evx_rt_ui_rb           = (ppc_op_form_evx << 16) | 0x6,
                ppc_op_subform_evx_bf_ra_rb           = (ppc_op_form_evx << 16) | 0x7,
                ppc_op_subform_evx_rt_ra_ui           = (ppc_op_form_evx << 16) | 0x8,
                ppc_op_subform_evx_rt_si              = (ppc_op_form_evx << 16) | 0x9,
                // evs form
                ppc_op_subform_evs_rt_ra_rb_bfa       = (ppc_op_form_evs << 16) | 0x1,
            };

            // subform type to form type
            constexpr size_t ppc_subform_to_form(size_t subform_type){
                return (subform_type >> 16);
            }

            /////////////////////////////////////////////////////////////////////////
            // ALU types / Operand types.
            ////////////////////////////////////////////////////////////////////////
            enum ppc_opr_type {
                opr_i       = 0x1,               // immediate
                opr_r       = 0x2,               // gpr
                opr_s       = 0x3,               // spr
                opr_m       = 0x4,               // msr
                opr_p       = 0x5,               // pmr
                opr_n       = 0x6,               // null operand
            };

            enum ppc_fu_type {
                ppc_fu_su1        = 0x1,         // simple unit 1
                ppc_fu_su2        = 0x6,         // simple unit 2
                ppc_fu_bu         = 0x2,         // branch unit
                ppc_fu_mu         = 0x3,         // multiple unit
                ppc_fu_lsu        = 0x4,         // load/store unit
                ppc_fu_nu         = 0x5,         // dummy null unit
            };

            /////////////////////////////////////////////////////////////////////////
            // Arguments to string conversion functions
            //
            //
            ////////////////////////////////////////////////////////////////////////
            // i form
            static inline std::string tostr_i_li(uint32_t arg0){
                return "DISP=" + TIS<int16_t>(arg0 << 2);
            }
            // b form
            static inline std::string tostr_b_bo_bi_bd(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "BO=" + TSH(arg0) + ",BI=" + TSH(arg1) + ",DISP=" + TIS<int16_t>(arg2 << 2);
            }
            // sc form
            static inline std::string tostr_sc_lev(uint32_t arg0){
                return "LEV=" + TSH(arg0);
            }
            static inline std::string tostr_sc(){
                return "";
            }
            // d form
            static inline std::string tostr_d_rt_ra_d(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RT=r" + TS(arg0) + ",RA=r" + TS(arg1) + ",D=" + TIS<int16_t>(arg2);
            }
            static inline std::string tostr_d_rt_ra_si(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RT=r" + TS(arg0) + ",RA=r" + TS(arg1) + ",SI=" + TIS<int16_t>(arg2);
            }
            static inline std::string tostr_d_rs_ra_d(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RS=r" + TS(arg0) + ",RA=r" + TS(arg1) + ",D=" + TIS<int16_t>(arg2);
            }
            static inline std::string tostr_d_rs_ra_ui(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RS=r" + TS(arg0) + ",RA=r" + TS(arg1) + ",UI=" + TIS<uint16_t>(arg2);
            }
            static inline std::string tostr_d_bf_l_ra_si(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3){
                return "BF=" + TSH(arg0) + ",L=" + TSH(arg1) + ",RA=r" + TS(arg1) + ",SI=" + TIS<int16_t>(arg2);
            }
            static inline std::string tostr_d_bf_l_ra_ui(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3){
                return "BF=" + TSH(arg0) + ",L=" + TSH(arg1) + ",RA=r" + TS(arg1) + ",UI=" + TIS<uint16_t>(arg2);
            }
            static inline std::string tostr_d_to_ra_si(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "TO=" + TSH(arg0) + ",RA=r" + TS(arg1) + ",SI=" + TIS<int16_t>(arg2);
            }
            // x form
            static inline std::string tostr_x_rt_ra(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) + ",RA=r" + TS(arg1);
            }
            static inline std::string tostr_x_rt_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RT=r" + TS(arg0) + ",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_x_rt_ra_nb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RT=r" + TS(arg0) + ",RA=r" + TS(arg1) + ",NB=" + TSH(arg2);
            }
            static inline std::string tostr_x_rt_sr(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) + ",SR=" + TSH(arg1);
            }
            static inline std::string tostr_x_rt_rb(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) + ",RB=" + TS(arg1);
            }
            static inline std::string tostr_x_rt(uint32_t arg0){
                return "RT=r" + TS(arg0);
            }
            static inline std::string tostr_x_rs_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RS=r" + TS(arg0) + ",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_x_rs_ra_nb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RS=r" + TS(arg0) + ",RA=r" + TS(arg1) + ",NB=" + TSH(arg2);
            }
            static inline std::string tostr_x_rs_ra_sh(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RS=r" + TS(arg0) + ",RA=r" + TS(arg1) + ",SH=" + TSH(arg2);
            }
            static inline std::string tostr_x_rs_ra(uint32_t arg0, uint32_t arg1){
                return "RS=r" + TS(arg0) + ",RA=r" + TS(arg1);
            }
            static inline std::string tostr_x_rs_sr(uint32_t arg0, uint32_t arg1){
                return "RS=r" + TS(arg0) + ",SR=" + TSH(arg1);
            }
            static inline std::string tostr_x_rs_rb(uint32_t arg0, uint32_t arg1){
                return "RS=r" + TS(arg0) + ",RB=r" + TS(arg1);
            }
            static inline std::string tostr_x_rs(uint32_t arg0){
                return "RS=r" + TS(arg0);
            }
            static inline std::string tostr_x_rs_l(uint32_t arg0, uint32_t arg1){
                return "RS=r" + TS(arg0) + ",L=" + TSH(arg1);
            }
            static inline std::string tostr_x_th_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "TH=" + TSH(arg0) + ",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_x_bf_l_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3){
                return "BF=" + TSH(arg0) + ",L=" + TSH(arg1) + ",RA=r" + TS(arg2) + ",RB=r" + TS(arg3);
            }
            static inline std::string tostr_x_bf_bfa(uint32_t arg0, uint32_t arg1){
                return "BF=" + TSH(arg0) + ",BFA=" + TSH(arg1);
            }
            static inline std::string tostr_x_bf(uint32_t arg0){
                return "BF=" + TSH(arg0);
            }
            static inline std::string tostr_x_ct(uint32_t arg0){
                return "CT=" + TSH(arg0);
            }
            static inline std::string tostr_x_ct_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "CT=" + TSH(arg0) + ",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_x_l_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "L=" + TSH(arg0) + ",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_x_l_rb(uint32_t arg0, uint32_t arg1){
                return "L=" + TSH(arg0) + ",RB=r" + TS(arg1);
            }
            static inline std::string tostr_x_l(uint32_t arg0){
                return "L=" + TSH(arg0);
            }
            static inline std::string tostr_x_to_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "TO=" + TSH(arg0) + ",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_x_bt(uint32_t arg0){
                return "BT=" + TSH(arg0);
            }
            static inline std::string tostr_x_ra_rb(uint32_t arg0, uint32_t arg1){
                return "RA=r" + TS(arg0) + ",RB=r" + TS(arg1);
            }
            static inline std::string tostr_x_rb(uint32_t arg0){
                return "RB=r" + TS(arg0);
            }
            static inline std::string tostr_x_e(uint32_t arg0){
                return "E=" + TSH(arg0);
            }
            static inline std::string tostr_x_wc(uint32_t arg0){
                return "WC=" + TSH(arg0);
            }
            static inline std::string tostr_x_t_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "T=" + TSH(arg0) + ",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_x_mo(uint32_t arg0){
                return "MO=" + TSH(arg0);
            }
            // xl form
            static inline std::string tostr_xl_bt_ba_bb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "BT=" + TSH(arg0) + ",BA=" + TSH(arg1) + ",BB=" + TSH(arg2);
            } 
            static inline std::string tostr_xl_bo_bi_bh(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "BO=" + TSH(arg0) + ",BI=" + TSH(arg1) + ",BH=" + TSH(arg2);
            }
            static inline std::string tostr_xl_bf_bfa(uint32_t arg0, uint32_t arg1){
                return "BF=" + TSH(arg0) + ",BFA=" + TSH(arg1);
            }
            static inline std::string tostr_xl_oc(uint32_t arg0){
                return "OC=" + TSH(arg0);
            }
            // xfx form
            static inline std::string tostr_xfx_rt_spr(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) +",SPR=" + TSH(arg1);
            }
            static inline std::string tostr_xfx_rt(uint32_t arg0){
                return "RT=r" + TS(arg0);
            }
            static inline std::string tostr_xfx_rt_fxm(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) +",FXM=" + TSH(arg1);
            }
            static inline std::string tostr_xfx_rt_pmr(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) +",PMR=" + TSH(arg1);
            }
            static inline std::string tostr_xfx_rs_fxm(uint32_t arg0, uint32_t arg1){
                return "RS=r" + TS(arg0) +",FXM=" + TSH(arg1);
            }
            static inline std::string tostr_xfx_rs_spr(uint32_t arg0, uint32_t arg1){
                return "RS=r" + TS(arg0) +",SPR=" + TSH(arg1);
            }
            static inline std::string tostr_xfx_rs_pmr(uint32_t arg0, uint32_t arg1){
                return "RS=r" + TS(arg0) +",PMR=" + TSH(arg1);
            }
            // xo form
            static inline std::string tostr_xo_rt_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RT=r" + TS(arg0) +",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_xo_rt_ra(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) +",RA=r" + TS(arg1);
            }
            // a form
            static inline std::string tostr_a_rt_ra_rb_bc(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3){
                return "RT=r" + TS(arg0) +",RA=r" + TS(arg1) + ",RB=r" + TS(arg2) + ",BC=" + TSH(arg3);
            }
            // m form
            static inline std::string tostr_m_rs_ra_rb_mb_me(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
                return "RS=r" + TS(arg0) +",RA=r" + TS(arg1) + ",RB=r" + TS(arg2) + ",MB=" + TSH(arg3) + ",ME=" + TSH(arg4);
            }
            static inline std::string tostr_m_rs_ra_sh_mb_me(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
                return "RS=r" + TS(arg0) +",RA=r" + TS(arg1) + ",SH=" + TSH(arg2) + ",MB=" + TSH(arg3) + ",ME=" + TSH(arg4);
            }
            // evx form
            static inline std::string tostr_evx_rs_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RS=r" + TS(arg0) +",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_evx_rs_ra_ui(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RS=r" + TS(arg0) +",RA=r" + TS(arg1) + ",UI=" + TSH(arg2);
            }
            static inline std::string tostr_evx_rt_rb(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) +",RB=r" + TS(arg1);
            }
            static inline std::string tostr_evx_rt_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RT=r" + TS(arg0) + ",RA=r" + TS(arg1) +",RB=r" + TS(arg2);
            }
            static inline std::string tostr_evx_rt_ra(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) + ",RA=r" + TS(arg1);
            }
            static inline std::string tostr_evx_rt_ui_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RT=r" + TS(arg0) + ",UI=" + TSH(arg1) +",RB=r" + TS(arg2);
            }
            static inline std::string tostr_evx_bf_ra_rb(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "BF=" + TSH(arg0) +",RA=r" + TS(arg1) + ",RB=r" + TS(arg2);
            }
            static inline std::string tostr_evx_rt_ra_ui(uint32_t arg0, uint32_t arg1, uint32_t arg2){
                return "RT=r" + TS(arg0) +",RA=r" + TS(arg1) + ",UI=" + TSH(arg2);
            }
            static inline std::string tostr_evx_rt_si(uint32_t arg0, uint32_t arg1){
                return "RT=r" + TS(arg0) +",SI=" + TIS<int16_t>(arg1);
            }
            // evs form
            static inline std::string tostr_evs_rt_ra_rb_bfa(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3){
                return "RT=r" + TS(arg0) + ",RA=r" + TS(arg1) +",RB=r" + TS(arg2) + ",BFA=" + TSH(arg3);
            }


            /////////////////////////////////////////////////////////////////////////
            // template specialization for opcode group fields
            //
            // NOTE : these bit fields are defined for little endian machines. They
            //        will only work on little endian (x86/x86_64) machines.
            /////////////////////////////////////////////////////////////////////////

            // some typedefs
            typedef std::vector<uint32_t>       ppc_argsvt;
            typedef std::vector<ppc_opr_type>   ppc_oprsvt;


#define PPC_OPC_ARG_INITIALIZER()                                                      \
            std::string to_str()  { return "NULL"; }                                   \
            ppc_argsvt args()     { return ppc_argsvt { 0xffffffff }; }                \
            ppc_oprsvt oprs()     { return ppc_oprsvt { opr_n }; }

            //
            // generic declaration.
            // First template parameter specifies instruction group type
            // Second template parameter specifies instruction sub group type
            template<size_t, size_t> struct ppc_op_bf {};

            //////////////////////////
            // i form
            /////////////////////////
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_i, ppc_subform_type> {
                uint32_t   resv0   : 2;
                uint32_t   li      : 24;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // i_li
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_i, ppc_op_subform_i_li>::args()     { return ppc_argsvt {li}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_i, ppc_op_subform_i_li>::oprs()     { return ppc_oprsvt {opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_i, ppc_op_subform_i_li>::to_str()   { return tostr_i_li(li); }


            ////////////////////////////
            // b type
            ///////////////////////////
            // FIXME : fix for to_str
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_b, ppc_subform_type> {
                uint32_t   resv0   : 2;
                uint32_t   bd      : 14;
                uint32_t   bi      : 5;
                uint32_t   bo      : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // b_bo_bi_bd
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_b, ppc_op_subform_b_bo_bi_bd>::args()   { return ppc_argsvt {bo,bi,bd}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_b, ppc_op_subform_b_bo_bi_bd>::oprs()   { return ppc_oprsvt {opr_i,opr_i,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_b, ppc_op_subform_b_bo_bi_bd>::to_str() { return tostr_b_bo_bi_bd(bo,bi,bd); }
            
            //////////////////////////////
            // sc form
            //////////////////////////////
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_sc, ppc_subform_type> {
                uint32_t   resv0   : 5;
                uint32_t   lev     : 7;
                uint32_t   resv1   : 14;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // sc
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_sc, ppc_op_subform_sc>::oprs()          { return ppc_oprsvt {opr_n}; }
            template<> std::string    ppc_op_bf<ppc_op_form_sc, ppc_op_subform_sc>::to_str()        { return ""; }
            // sc_lev
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_sc, ppc_op_subform_sc_lev>::args()      { return ppc_argsvt {lev}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_sc, ppc_op_subform_sc_lev>::oprs()      { return ppc_oprsvt {opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_sc, ppc_op_subform_sc_lev>::to_str()    { return tostr_sc_lev(lev); }
           
            /////////////////////////////// 
            // d form
            ///////////////////////////////

            // Generic form (2 GPR, 1 disp form)
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_d, ppc_subform_type> {
                uint32_t   arg2    : 16;
                uint32_t   arg1    : 5;
                uint32_t   arg0    : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // d_rt_ra_d
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rt_ra_d>::args()      { return ppc_argsvt {arg0,arg2,arg1}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rt_ra_d>::oprs()      { return ppc_oprsvt {opr_r,opr_i,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rt_ra_d>::to_str()    { return tostr_d_rt_ra_d(arg0,arg1,arg2); }
            // d_rt_ra_si
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rt_ra_si>::args()     { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rt_ra_si>::oprs()     { return ppc_oprsvt {opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rt_ra_si>::to_str()   { return tostr_d_rt_ra_si(arg0,arg1,arg2); }
            // d_rs_ra_d
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rs_ra_d>::args()      { return ppc_argsvt {arg0,arg2,arg1}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rs_ra_d>::oprs()      { return ppc_oprsvt {opr_r,opr_i,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rs_ra_d>::to_str()    { return tostr_d_rs_ra_d(arg0,arg1,arg2); }
            // d_rs_ra_ui
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rs_ra_ui>::args()     { return ppc_argsvt {arg1,arg0,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rs_ra_ui>::oprs()     { return ppc_oprsvt {opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_rs_ra_ui>::to_str()   { return tostr_d_rs_ra_ui(arg0,arg1,arg2); }
            // d_to_ra_si
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_to_ra_si>::args()     { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_to_ra_si>::oprs()     { return ppc_oprsvt {opr_i,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_to_ra_si>::to_str()   { return tostr_d_to_ra_si(arg0,arg1,arg2); }
            // d_bf_l_ra_si
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_bf_l_ra_si>::args()   { return ppc_argsvt {(arg0 >> 2),(arg0 & 0x1),arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_bf_l_ra_si>::oprs()   { return ppc_oprsvt {opr_i,opr_i,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_bf_l_ra_si>::to_str() { return tostr_d_bf_l_ra_si((arg0 >> 2),(arg0 & 0x1),arg1,arg2); }
            // d_bf_l_ra_ui
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_bf_l_ra_ui>::args()   { return ppc_argsvt {(arg0 >> 2),(arg0 & 0x1),arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_bf_l_ra_ui>::oprs()   { return ppc_oprsvt {opr_i,opr_i,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_d, ppc_op_subform_d_bf_l_ra_ui>::to_str() { return tostr_d_bf_l_ra_ui((arg0 >> 2),(arg0 & 0x1),arg1,arg2); }

            // NOTE : DS form is only used in 64 bit mode          

            //////////////
            // x form
            //////////////
            
            // Generic form (3 GPR form)
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_x, ppc_subform_type> {
                uint32_t   rc      : 1;
                uint32_t   xo      : 10;
                uint32_t   arg2    : 5;
                uint32_t   arg1    : 5;
                uint32_t   arg0    : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // x_rt_ra
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_ra>::args()        { return ppc_argsvt {arg0,arg1}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_ra>::oprs()        { return ppc_oprsvt {opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_ra>::to_str()      { return tostr_x_rt_ra(arg0,arg1); }
            // x_rt_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_ra_rb>::args()     { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_ra_rb>::oprs()     { return ppc_oprsvt {opr_r,opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_ra_rb>::to_str()   { return tostr_x_rt_ra_rb(arg0,arg1,arg2); }
            // x_rt_ra_nb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_ra_nb>::args()     { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_ra_nb>::oprs()     { return ppc_oprsvt {opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_ra_nb>::to_str()   { return tostr_x_rt_ra_nb(arg0,arg1,arg2) ; }
            // x_rt_sr [ FIXME: Verify ]
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_sr>::args()        { return ppc_argsvt {arg0,(arg1 & 0xf)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_sr>::oprs()        { return ppc_oprsvt {opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_sr>::to_str()      { return tostr_x_rt_sr(arg0,(arg1 & 0xf)) ; }
            // x_rt_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_rb>::args()        { return ppc_argsvt {arg0,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_rb>::oprs()        { return ppc_oprsvt {opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt_rb>::to_str()      { return tostr_x_rt_rb(arg0,arg2); }
            // x_rt
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt>::args()           { return ppc_argsvt {arg0}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt>::oprs()           { return ppc_oprsvt {opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rt>::to_str()         { return tostr_x_rt(arg0); }
            // x_rs_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra_rb>::args()     { return ppc_argsvt {arg1,arg0,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra_rb>::oprs()     { return ppc_oprsvt {opr_r,opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra_rb>::to_str()   { return tostr_x_rs_ra_rb(arg0,arg1,arg2); } 
            // x_rs_ra_nb [FIXME: Verify argumnents order]
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra_nb>::args()     { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra_nb>::oprs()     { return ppc_oprsvt {opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra_nb>::to_str()   { return tostr_x_rs_ra_nb(arg0,arg1,arg2) ; }
            // x_rs_ra_sh
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra_sh>::args()     { return ppc_argsvt {arg1,arg0,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra_sh>::oprs()     { return ppc_oprsvt {opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra_sh>::to_str()   { return tostr_x_rs_ra_sh(arg0,arg1,arg2) ; }
            // x_rs_ra
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra>::args()        { return ppc_argsvt {arg1,arg0}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra>::oprs()        { return ppc_oprsvt {opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_ra>::to_str()      { return tostr_x_rs_ra(arg0,arg1); }
            // x_rs_sr [ FIXME: Verify ]
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_sr>::args()        { return ppc_argsvt {arg0,(arg1 & 0xf)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_sr>::oprs()        { return ppc_oprsvt {opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_sr>::to_str()      { return tostr_x_rs_sr(arg0,(arg1 & 0xf)) ; }
            // x_rs_rb [FIXME: Verify]
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_rb>::args()        { return ppc_argsvt {arg0,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_rb>::oprs()        { return ppc_oprsvt {opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_rb>::to_str()      { return tostr_x_rs_rb(arg0,arg2); }
            // x_rs
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs>::args()           { return ppc_argsvt {arg0}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs>::oprs()           { return ppc_oprsvt {opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs>::to_str()         { return tostr_x_rs(arg0); }
            // x_rs_l
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_l>::args()         { return ppc_argsvt {arg0,(arg1 & 0x1)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_l>::oprs()         { return ppc_oprsvt {opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rs_l>::to_str()       { return tostr_x_rs_l(arg0,(arg1 & 0x1)); }
            // x_th_ra_rb [FIXME: Verify]
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_th_ra_rb>::args()     { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_th_ra_rb>::oprs()     { return ppc_oprsvt {opr_i,opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_th_ra_rb>::to_str()   { return tostr_x_th_ra_rb(arg0,arg1,arg2); }
            // x_bf_l_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_bf_l_ra_rb>::args()   { return ppc_argsvt {(arg0 >> 2),(arg0 & 0x1),arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_bf_l_ra_rb>::oprs()   { return ppc_oprsvt {opr_i,opr_i,opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_bf_l_ra_rb>::to_str() { return tostr_x_bf_l_ra_rb((arg0 >> 2),(arg0 & 0x1),arg1,arg2); }
            // x_bf
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_bf>::args()           { return ppc_argsvt {(arg0 >> 2)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_bf>::oprs()           { return ppc_oprsvt {opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_bf>::to_str()         { return tostr_x_bf(arg0 >> 2); }
            // x_ct
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_ct>::args()           { return ppc_argsvt {(arg0 & 0xf)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_ct>::oprs()           { return ppc_oprsvt {opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_ct>::to_str()         { return tostr_x_ct(arg0 & 0xf); }
            // x_ct_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_ct_ra_rb>::args()     { return ppc_argsvt {(arg0 & 0xf),arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_ct_ra_rb>::oprs()     { return ppc_oprsvt {opr_i,opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_ct_ra_rb>::to_str()   { return tostr_x_ct_ra_rb((arg0 & 0xf),arg1,arg2); }
            // x_l_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_l_ra_rb>::args()      { return ppc_argsvt {arg1,arg2,(arg0 & 0x3)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_l_ra_rb>::oprs()      { return ppc_oprsvt {opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_l_ra_rb>::to_str()    { return tostr_x_l_ra_rb((arg0 & 0x3),arg1,arg2); }
            // x_l
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_l>::args()            { return ppc_argsvt {(arg0 & 0x3)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_l>::oprs()            { return ppc_oprsvt {opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_l>::to_str()          { return tostr_x_l(arg0 & 0x3); }
            // x_to_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_to_ra_rb>::args()     { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_to_ra_rb>::oprs()     { return ppc_oprsvt {opr_i,opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_to_ra_rb>::to_str()   { return tostr_x_to_ra_rb(arg0,arg1,arg2); }
            // x_bt
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_bt>::args()           { return ppc_argsvt {arg0}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_bt>::oprs()           { return ppc_oprsvt {opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_bt>::to_str()         { return tostr_x_bt(arg0); }
            // x_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_ra_rb>::args()        { return ppc_argsvt {arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_ra_rb>::oprs()        { return ppc_oprsvt {opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_ra_rb>::to_str()      { return tostr_x_ra_rb(arg1,arg2); }
            // x_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rb>::args()           { return ppc_argsvt {arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rb>::oprs()           { return ppc_oprsvt {opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_rb>::to_str()         { return tostr_x_rb(arg2); }
            // x
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x>::oprs()              { return ppc_oprsvt {opr_n}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x>::to_str()            { return ""; }
            // x_e
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_e>::args()            { return ppc_argsvt {(arg2 >> 4)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_e>::oprs()            { return ppc_oprsvt {opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_e>::to_str()          { return tostr_x_e(arg2 >> 4); }
            // x_mo
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_mo>::args()           { return ppc_argsvt {arg0}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_mo>::oprs()           { return ppc_oprsvt {opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_x, ppc_op_subform_x_mo>::to_str()         { return tostr_x_mo(arg0); }

            //////////////
            // xl form
            //////////////
            
            // Generic form (3 immediate form)
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_xl, ppc_subform_type> {
                uint32_t   lk      : 1;
                uint32_t   xo      : 10;
                uint32_t   arg2    : 5;
                uint32_t   arg1    : 5;
                uint32_t   arg0    : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // xl_bt_ba_bb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xl, ppc_op_subform_xl_bt_ba_bb>::args()   { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xl, ppc_op_subform_xl_bt_ba_bb>::oprs()   { return ppc_oprsvt {opr_i,opr_i,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xl, ppc_op_subform_xl_bt_ba_bb>::to_str() { return tostr_xl_bt_ba_bb(arg0,arg1,arg2); }
            // xl_bo_bi_bh
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xl, ppc_op_subform_xl_bo_bi_bh>::args()   { return ppc_argsvt {arg0,arg1,(arg2 & 0x3)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xl, ppc_op_subform_xl_bo_bi_bh>::oprs()   { return ppc_oprsvt {opr_i,opr_i,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xl, ppc_op_subform_xl_bo_bi_bh>::to_str() { return tostr_xl_bo_bi_bh(arg0,arg1,(arg2 & 0x3)); } 
            // xl_bf_bfa
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xl, ppc_op_subform_xl_bf_bfa>::args()     { return ppc_argsvt {(arg0 >> 2),(arg1 >> 2)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xl, ppc_op_subform_xl_bf_bfa>::oprs()     { return ppc_oprsvt {opr_i,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xl, ppc_op_subform_xl_bf_bfa>::to_str()   { return tostr_xl_bf_bfa((arg0 >> 2),(arg1 >> 2)); } 

            /////////////////////////
            // xfx form
            /////////////////////////
            //
            // Generic form (1 GPR, 1 SPR form)
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_xfx, ppc_subform_type> {
                uint32_t   resv0   : 1;
                uint32_t   xo      : 10;
                uint32_t   arg1    : 10;
                uint32_t   arg0    : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            ///////////////
            //
            // FIXME : Verify operand ordering of mtspr/mfspr/mtpmr/mfpmr instruction types.
            //////////////
            // xfx_rt_spr [ FIXME: May need to process arg1 for correct SPRNO.May also need to check args order ]
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rt_spr>::args()     { return ppc_argsvt {arg0,arg1}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rt_spr>::oprs()     { return ppc_oprsvt {opr_r,opr_s}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rt_spr>::to_str()   { return tostr_xfx_rt_spr(arg0,arg1); }
            // xfx_rt
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rt>::args()         { return ppc_argsvt {arg0}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rt>::oprs()         { return ppc_oprsvt {opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rt>::to_str()       { return tostr_xfx_rt(arg0); }
            // xfx_rt_pmr
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rt_pmr>::args()     { return ppc_argsvt {arg0,arg1}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rt_pmr>::oprs()     { return ppc_oprsvt {opr_r,opr_p}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rt_pmr>::to_str()   { return tostr_xfx_rt_pmr(arg0,arg1); }
            // xfx_rs_fxm
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rs_fxm>::args()     { return ppc_argsvt {arg0,((arg1 >> 1) & 0xff)}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rs_fxm>::oprs()     { return ppc_oprsvt {opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rs_fxm>::to_str()   { return tostr_xfx_rs_fxm(arg0,((arg1 >> 1) & 0xff)); }
            // xfx_rs_spr
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rs_spr>::args()     { return ppc_argsvt {arg0,arg1}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rs_spr>::oprs()     { return ppc_oprsvt {opr_r,opr_s}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rs_spr>::to_str()   { return tostr_xfx_rs_spr(arg0,arg1); }
            // xfx_rs_pmr
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rs_pmr>::args()     { return ppc_argsvt {arg0,arg1}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rs_pmr>::oprs()     { return ppc_oprsvt {opr_r,opr_p}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xfx, ppc_op_subform_xfx_rs_pmr>::to_str()   { return tostr_xfx_rs_pmr(arg0,arg1); }

            /////////////////////////
            // xo form
            /////////////////////////
            //
            // Generic form (3 GPR form)
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_xo, ppc_subform_type> {
                uint32_t   rc      : 1;
                uint32_t   xo      : 9;
                uint32_t   oe      : 1;
                uint32_t   arg2    : 5;
                uint32_t   arg1    : 5;
                uint32_t   arg0    : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // xo_rt_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xo, ppc_op_subform_xo_rt_ra_rb>::args()     { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xo, ppc_op_subform_xo_rt_ra_rb>::oprs()     { return ppc_oprsvt {opr_r,opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xo, ppc_op_subform_xo_rt_ra_rb>::to_str()   { return tostr_xo_rt_ra_rb(arg0,arg1,arg2); }
            // xo_rt_ra
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_xo, ppc_op_subform_xo_rt_ra>::args()        { return ppc_argsvt {arg0,arg1}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_xo, ppc_op_subform_xo_rt_ra>::oprs()        { return ppc_oprsvt {opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_xo, ppc_op_subform_xo_rt_ra>::to_str()      { return tostr_xo_rt_ra(arg0,arg1); }

            /////////////////////////
            // a form
            /////////////////////////
            //
            // Generic form (4 GPR form)
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_a, ppc_subform_type> {
                uint32_t   rc      : 1;
                uint32_t   xo      : 5;
                uint32_t   arg3    : 5;
                uint32_t   arg2    : 5;
                uint32_t   arg1    : 5;
                uint32_t   arg0    : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // a_rt_ra_rb_bc
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_a, ppc_op_subform_a_rt_ra_rb_bc>::args()    { return ppc_argsvt {arg0,arg1,arg2,arg3}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_a, ppc_op_subform_a_rt_ra_rb_bc>::oprs()    { return ppc_oprsvt {opr_r,opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_a, ppc_op_subform_a_rt_ra_rb_bc>::to_str()  { return tostr_a_rt_ra_rb_bc(arg0,arg1,arg2,arg3); }

            /////////////////////////
            // m form
            /////////////////////////
            //
            // Generic form (2/3 GPR, 2/3 imm form)
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_m, ppc_subform_type> {
                uint32_t   rc      : 1;
                uint32_t   arg4    : 5;
                uint32_t   arg3    : 5;
                uint32_t   arg2    : 5;
                uint32_t   arg1    : 5;
                uint32_t   arg0    : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // m_rs_ra_rb_mb_me
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_m, ppc_op_subform_m_rs_ra_rb_mb_me>::args()   { return ppc_argsvt {arg0,arg1,arg2,arg3,arg4}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_m, ppc_op_subform_m_rs_ra_rb_mb_me>::oprs()   { return ppc_oprsvt {opr_r,opr_r,opr_r,opr_i,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_m, ppc_op_subform_m_rs_ra_rb_mb_me>::to_str() { return tostr_m_rs_ra_rb_mb_me(arg0,arg1,arg2,arg3,arg4); }
            // m_rs_ra_sh_mb_me
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_m, ppc_op_subform_m_rs_ra_sh_mb_me>::args()   { return ppc_argsvt {arg0,arg1,arg2,arg3,arg4}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_m, ppc_op_subform_m_rs_ra_sh_mb_me>::oprs()   { return ppc_oprsvt {opr_r,opr_r,opr_i,opr_i,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_m, ppc_op_subform_m_rs_ra_sh_mb_me>::to_str() { return tostr_m_rs_ra_sh_mb_me(arg0,arg1,arg2,arg3,arg4); }

            //
            /////////////////////////
            // evx form
            /////////////////////////
            //
            // Generic form (3 GPR spe form)
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_evx, ppc_subform_type> {
                uint32_t   xo      : 11;
                uint32_t   arg2    : 5;
                uint32_t   arg1    : 5;
                uint32_t   arg0    : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // evx_rs_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rs_ra_rb>::args()   { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rs_ra_rb>::oprs()   { return ppc_oprsvt {opr_r,opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rs_ra_rb>::to_str() { return tostr_evx_rs_ra_rb(arg0,arg1,arg2); }
            // evx_rs_ra_ui
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rs_ra_ui>::args()   { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rs_ra_ui>::oprs()   { return ppc_oprsvt {opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rs_ra_ui>::to_str() { return tostr_evx_rs_ra_ui(arg0,arg1,arg2); }
            // evx_rt_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_rb>::args()      { return ppc_argsvt {arg0,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_rb>::oprs()      { return ppc_oprsvt {opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_rb>::to_str()    { return tostr_evx_rt_rb(arg0,arg2); }
            // evx_rt_ra_rb
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ra_rb>::args()   { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ra_rb>::oprs()   { return ppc_oprsvt {opr_r,opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ra_rb>::to_str() { return tostr_evx_rt_ra_rb(arg0,arg1,arg2); }
            // evx_rt_ra
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ra>::args()      { return ppc_argsvt {arg0,arg1}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ra>::oprs()      { return ppc_oprsvt {opr_r,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ra>::to_str()    { return tostr_evx_rt_ra(arg0,arg1); }
            // evx_rt_ui_rb [ FIXME: Verify args order ]
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ui_rb>::args()   { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ui_rb>::oprs()   { return ppc_oprsvt {opr_r,opr_i,opr_r}; }
            template<> std::string    ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ui_rb>::to_str() { return tostr_evx_rt_ui_rb(arg0,arg1,arg2); }
            // evx_bf_ra_rb
            //template<> ppc_argsvt           ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_bf_ra_rb>::args()   { return ppc_argsvt {arg0,arg1,arg2}; }
            //template<> std::string          ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_bf_ra_rb>::to_str() { return "r" + TS(arg0) + "," + TSH(arg1) + ",r" + TS(arg2); }
            // evx_rt_ra_ui
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ra_ui>::args()   { return ppc_argsvt {arg0,arg1,arg2}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ra_ui>::oprs()   { return ppc_oprsvt {opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_ra_ui>::to_str() { return tostr_evx_rt_ra_ui(arg0,arg1,arg2); }
            // evx_rt_si
            //template<> ppc_argsvt           ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_si>::args()      { return ppc_argsvt {arg0,arg1}; }
            //template<> std::string          ppc_op_bf<ppc_op_form_evx, ppc_op_subform_evx_rt_si>::to_str()    { return "r" + TS(arg0) + "," + TSH(arg1); }

            /////////////////////////
            // evs form
            /////////////////////////
            //
            // Generic form (3 GPR, 1 imm spe form)
            template<size_t ppc_subform_type> struct ppc_op_bf<ppc_op_form_evs, ppc_subform_type> {
                uint32_t   arg3    : 3;
                uint32_t   xo      : 8;
                uint32_t   arg2    : 5;
                uint32_t   arg1    : 5;
                uint32_t   arg0    : 5;
                uint32_t   opc     : 6;
                
                PPC_OPC_ARG_INITIALIZER()
            };

            // evs_rt_ra_rb_bfa
            template<> ppc_argsvt     ppc_op_bf<ppc_op_form_evs, ppc_op_subform_evs_rt_ra_rb_bfa>::args()   { return ppc_argsvt {arg0,arg1,arg2, arg3}; }
            template<> ppc_oprsvt     ppc_op_bf<ppc_op_form_evs, ppc_op_subform_evs_rt_ra_rb_bfa>::oprs()   { return ppc_oprsvt {opr_r,opr_r,opr_r,opr_i}; }
            template<> std::string    ppc_op_bf<ppc_op_form_evs, ppc_op_subform_evs_rt_ra_rb_bfa>::to_str() { return tostr_evs_rt_ra_rb_bfa(arg0,arg1,arg2,arg3); }

            //////////////////////////////////////////////////////////////////////////
            // decoding engine
            // ///////////////////////////////////////////////////////////////////////

            // templated union
            template<size_t OP_SUBGRP> union ppc_op_bfu {
                uint32_t                                                   opcode;
                ppc_op_bf<ppc_subform_to_form(OP_SUBGRP), OP_SUBGRP>       bf;
            };

            // Suggestion : Use a compiler supporting c++0x to exploit move
            //              semantics.
            struct ppc_op_dec_base {
                virtual std::vector<uint32_t> decode(uint32_t opcode) = 0;
                virtual std::string           to_str(uint32_t opcode) = 0;
            };
           
            template<size_t OP_SUBGRP> 
            struct ppc_op_dec : public ppc_op_dec_base {
                ppc_op_bfu<OP_SUBGRP>     bfu;

                std::vector<uint32_t> decode(uint32_t opcode) {
                    bfu.opcode = opcode;
                    return bfu.bf.args();
                }
                std::string to_str(uint32_t opcode) {
                    bfu.opcode = opcode;
                    return bfu.bf.to_str();
                }
            };

            ////////////////////
            //
            // All static objects for each subform type
            /////////////////////////////////////////
            //
            // i form
            static ppc_op_dec<ppc_op_subform_i_li>                   ppc_obj_subform_i_li;
            // b form
            static ppc_op_dec<ppc_op_subform_b_bo_bi_bd>             ppc_obj_subform_b_bo_bi_bd;
            // sc form
            static ppc_op_dec<ppc_op_subform_sc>                     ppc_obj_subform_sc;
            static ppc_op_dec<ppc_op_subform_sc_lev>                 ppc_obj_subform_sc_lev;
            // d form
            static ppc_op_dec<ppc_op_subform_d_rt_ra_d>              ppc_obj_subform_d_rt_ra_d;
            static ppc_op_dec<ppc_op_subform_d_rt_ra_si>             ppc_obj_subform_d_rt_ra_si;
            static ppc_op_dec<ppc_op_subform_d_rs_ra_d>              ppc_obj_subform_d_rs_ra_d;
            static ppc_op_dec<ppc_op_subform_d_rs_ra_ui>             ppc_obj_subform_d_rs_ra_ui;
            static ppc_op_dec<ppc_op_subform_d_bf_l_ra_si>           ppc_obj_subform_d_bf_l_ra_si;
            static ppc_op_dec<ppc_op_subform_d_bf_l_ra_ui>           ppc_obj_subform_d_bf_l_ra_ui;
            static ppc_op_dec<ppc_op_subform_d_to_ra_si>             ppc_obj_subform_d_to_ra_si;
            // x form
            static ppc_op_dec<ppc_op_subform_x_rt_ra>                ppc_obj_subform_x_rt_ra;
            static ppc_op_dec<ppc_op_subform_x_rt_ra_rb>             ppc_obj_subform_x_rt_ra_rb;
            static ppc_op_dec<ppc_op_subform_x_rt_ra_nb>             ppc_obj_subform_x_rt_ra_nb;
            static ppc_op_dec<ppc_op_subform_x_rt_sr>                ppc_obj_subform_x_rt_sr;
            static ppc_op_dec<ppc_op_subform_x_rt_rb>                ppc_obj_subform_x_rt_rb;
            static ppc_op_dec<ppc_op_subform_x_rt>                   ppc_obj_subform_x_rt;
            static ppc_op_dec<ppc_op_subform_x_rs_ra_rb>             ppc_obj_subform_x_rs_ra_rb;
            static ppc_op_dec<ppc_op_subform_x_rs_ra_nb>             ppc_obj_subform_x_rs_ra_nb;
            static ppc_op_dec<ppc_op_subform_x_rs_ra_sh>             ppc_obj_subform_x_rs_ra_sh;
            static ppc_op_dec<ppc_op_subform_x_rs_ra>                ppc_obj_subform_x_rs_ra;
            static ppc_op_dec<ppc_op_subform_x_rs_sr>                ppc_obj_subform_x_rs_sr;
            static ppc_op_dec<ppc_op_subform_x_rs_rb>                ppc_obj_subform_x_rs_rb;
            static ppc_op_dec<ppc_op_subform_x_rs>                   ppc_obj_subform_x_rs;
            static ppc_op_dec<ppc_op_subform_x_rs_l>                 ppc_obj_subform_x_rs_l;
            static ppc_op_dec<ppc_op_subform_x_th_ra_rb>             ppc_obj_subform_x_th_ra_rb;
            static ppc_op_dec<ppc_op_subform_x_bf_l_ra_rb>           ppc_obj_subform_x_bf_l_ra_rb;
            static ppc_op_dec<ppc_op_subform_x_bf_bfa>               ppc_obj_subform_x_bf_bfa;
            static ppc_op_dec<ppc_op_subform_x_bf>                   ppc_obj_subform_x_bf;
            static ppc_op_dec<ppc_op_subform_x_ct>                   ppc_obj_subform_x_ct;
            static ppc_op_dec<ppc_op_subform_x_ct_ra_rb>             ppc_obj_subform_x_ct_ra_rb;
            static ppc_op_dec<ppc_op_subform_x_l_ra_rb>              ppc_obj_subform_x_l_ra_rb;
            static ppc_op_dec<ppc_op_subform_x_l_rb>                 ppc_obj_subform_x_l_rb;
            static ppc_op_dec<ppc_op_subform_x_l>                    ppc_obj_subform_x_l;
            static ppc_op_dec<ppc_op_subform_x_to_ra_rb>             ppc_obj_subform_x_to_ra_rb;
            static ppc_op_dec<ppc_op_subform_x_bt>                   ppc_obj_subform_x_bt;
            static ppc_op_dec<ppc_op_subform_x_ra_rb>                ppc_obj_subform_x_ra_rb;
            static ppc_op_dec<ppc_op_subform_x_rb>                   ppc_obj_subform_x_rb;
            static ppc_op_dec<ppc_op_subform_x_e>                    ppc_obj_subform_x_e;
            static ppc_op_dec<ppc_op_subform_x_ih>                   ppc_obj_subform_x_ih;
            static ppc_op_dec<ppc_op_subform_x_t_ra_rb>              ppc_obj_subform_x_t_ra_rb;
            static ppc_op_dec<ppc_op_subform_x_mo>                   ppc_obj_subform_x_mo;
            static ppc_op_dec<ppc_op_subform_x>                      ppc_obj_subform_x;
            // xl form
            static ppc_op_dec<ppc_op_subform_xl_bt_ba_bb>            ppc_obj_subform_xl_bt_ba_bb;
            static ppc_op_dec<ppc_op_subform_xl_bo_bi_bh>            ppc_obj_subform_xl_bo_bi_bh;
            static ppc_op_dec<ppc_op_subform_xl_bf_bfa>              ppc_obj_subform_xl_bf_bfa;
            static ppc_op_dec<ppc_op_subform_xl>                     ppc_obj_subform_xl;
            // xfx form
            static ppc_op_dec<ppc_op_subform_xfx_rt_spr>             ppc_obj_subform_xfx_rt_spr;
            static ppc_op_dec<ppc_op_subform_xfx_rt>                 ppc_obj_subform_xfx_rt;
            static ppc_op_dec<ppc_op_subform_xfx_rt_pmr>             ppc_obj_subform_xfx_rt_pmr;
            static ppc_op_dec<ppc_op_subform_xfx_rs_fxm>             ppc_obj_subform_xfx_rs_fxm;
            static ppc_op_dec<ppc_op_subform_xfx_rs_spr>             ppc_obj_subform_xfx_rs_spr;
            static ppc_op_dec<ppc_op_subform_xfx_rs_pmr>             ppc_obj_subform_xfx_rs_pmr;
            // xo form
            static ppc_op_dec<ppc_op_subform_xo_rt_ra_rb>            ppc_obj_subform_xo_rt_ra_rb;
            static ppc_op_dec<ppc_op_subform_xo_rt_ra>               ppc_obj_subform_xo_rt_ra;
            // a form
            static ppc_op_dec<ppc_op_subform_a_rt_ra_rb_bc>          ppc_obj_subform_a_rt_ra_rb_bc;
            // m form
            static ppc_op_dec<ppc_op_subform_m_rs_ra_rb_mb_me>       ppc_obj_subform_m_rs_ra_rb_mb_me;
            static ppc_op_dec<ppc_op_subform_m_rs_ra_sh_mb_me>       ppc_obj_subform_m_rs_ra_sh_mb_me;
            // evx form
            static ppc_op_dec<ppc_op_subform_evx_rs_ra_rb>           ppc_obj_subform_evx_rs_ra_rb;
            static ppc_op_dec<ppc_op_subform_evx_rs_ra_ui>           ppc_obj_subform_evx_rs_ra_ui;
            static ppc_op_dec<ppc_op_subform_evx_rt_rb>              ppc_obj_subform_evx_rt_rb;
            static ppc_op_dec<ppc_op_subform_evx_rt_ra_rb>           ppc_obj_subform_evx_rt_ra_rb;
            static ppc_op_dec<ppc_op_subform_evx_rt_ra>              ppc_obj_subform_evx_rt_ra;
            static ppc_op_dec<ppc_op_subform_evx_rt_ui_rb>           ppc_obj_subform_evx_rt_ui_rb;
            static ppc_op_dec<ppc_op_subform_evx_bf_ra_rb>           ppc_obj_subform_evx_bf_ra_rb;
            static ppc_op_dec<ppc_op_subform_evx_rt_ra_ui>           ppc_obj_subform_evx_rt_ra_ui;
            static ppc_op_dec<ppc_op_subform_evx_rt_si>              ppc_obj_subform_evx_rt_si;
            // evs form
            static ppc_op_dec<ppc_op_subform_evs_rt_ra_rb_bfa>       ppc_obj_subform_evs_rt_ra_rb_bfa;

            ////////////////////////////////////////////////////////////////////////////////
            // compile time expressions for generating opcode masks
            ////////////////////////////////////////////////////////////////////////////////
            // opcode to mask
            constexpr uint32_t ppc_op_tomask(uint32_t opcode){ return (opcode & 0x3f) << 26; }

            // xo form
            constexpr uint32_t ppc_xo_tomask(uint32_t opcode, uint32_t xo, uint32_t oe, uint32_t rc){
                return ppc_op_tomask(opcode) | ((xo & 0x1ff) << 1) | ((oe & 0x1) << 10) | (rc & 0x1);
            }

            // x form
            // rc & eh refer to same parameter
            constexpr uint32_t ppc_x_tomask(uint32_t opcode, uint32_t xo, uint32_t rc=0){
                return ppc_op_tomask(opcode) | ((xo & 0x3ff) << 1) | (rc & 0x1);
            }

            // i form
            constexpr uint32_t ppc_i_tomask(uint32_t opcode, uint32_t aa, uint32_t lk){
                return ppc_op_tomask(opcode) | ((aa & 0x1) << 1) | (lk & 0x1);
            }

            // b form
            constexpr uint32_t ppc_b_tomask(uint32_t opcode, uint32_t aa, uint32_t lk){
                return ppc_op_tomask(opcode) | ((aa & 0x1) << 1) | (lk & 0x1);
            }

            // xl form
            constexpr uint32_t ppc_xl_tomask(uint32_t opcode, uint32_t xo, uint32_t lk){
                return ppc_op_tomask(opcode) | ((xo & 0x3ff) << 1) | (lk & 0x1);
            }

            // sc form
            constexpr uint32_t ppc_sc_tomask(uint32_t opcode){
                return ppc_op_tomask(opcode);
            }

            // m form
            constexpr uint32_t ppc_m_tomask(uint32_t opcode, uint32_t rc){
                return ppc_op_tomask(opcode) | (rc & 0x1);
            }

            // xfx form
            constexpr uint32_t ppc_xfx_tomask(uint32_t opcode, uint32_t xo, uint32_t rc=0){
                return ppc_op_tomask(opcode) | ((xo & 0x3ff) << 1) | (rc & 0x1);
            }

            // xfx-fxm form
            constexpr uint32_t ppc_xfx_fxm_tomask(uint32_t opcode, uint32_t xo, uint32_t fxm_p, uint32_t rc=0){
                return ppc_op_tomask(opcode) | ((fxm_p & 0x1) << 20) | ((xo & 0x3ff) << 1) | (rc & 0x1);
            }

            // a form
            constexpr uint32_t ppc_a_tomask(uint32_t opcode, uint32_t xo, uint32_t rc=0){
                return ppc_op_tomask(opcode) | ((xo & 0x1f) << 1) | (rc & 0x1);
            }

            // evx form
            constexpr uint32_t ppc_evx_tomask(uint32_t opcode, uint32_t xo){
                return ppc_op_tomask(opcode) | (xo & 0x7ff);
            }

            // evs form
            constexpr uint32_t ppc_evs_tomask(uint32_t opcode, uint32_t xo){
                return ppc_op_tomask(opcode) | ((xo & 0xff) << 3);
            }

            //constexpr
            //

            // opcode struct
            struct ppc_opcode {
                const uint32_t       opcode;
                const uint32_t       mask;
                const std::string    name;
                ppc_op_dec_base      *decptr;

                // argument decoding & print functions
                // NOTE : insn should be same as that used for extracting ppc_opcode struct
                std::string             to_str(uint32_t insn)    { return name + " " + decptr->to_str(insn); }
                std::vector<uint32_t>   to_args(uint32_t insn)   { return decptr->decode(insn); }
            };

            // standard masks
            static const uint32_t     xo_mask            = ppc_xo_tomask       (0x3f, 0x1ff, 0x1, 0x1);
            static const uint32_t     xl_mask            = ppc_xl_tomask       (0x3f, 0x3ff, 0x1);
            static const uint32_t     x_mask             = ppc_x_tomask        (0x3f, 0x3ff, 0x1);
            static const uint32_t     i_mask             = ppc_i_tomask        (0x3f, 0x1,   0x1);
            static const uint32_t     b_mask             = ppc_b_tomask        (0x3f, 0x1,   0x1);
            static const uint32_t     d_mask             = ppc_op_tomask       (0x3f);
            static const uint32_t     m_mask             = ppc_m_tomask        (0x3f, 0x1);
            static const uint32_t     xfx_mask           = ppc_xfx_tomask      (0x3f, 0x3ff, 0x1);
            static const uint32_t     xfx_fxm_mask       = ppc_xfx_fxm_tomask  (0x3f, 0x3ff, 0x1, 0x1);
            static const uint32_t     op_mask            = ppc_op_tomask       (0x3f);
            static const uint32_t     a_mask             = ppc_a_tomask        (0x3f, 0x1f, 0x1);
            static const uint32_t     evx_mask           = ppc_evx_tomask      (0x3f, 0x3ff);
            static const uint32_t     evs_mask           = ppc_evs_tomask      (0x3f, 0xff);

            //////////////////////
            // non standard masks
            //////////////////////
            // sc
            static const uint32_t     sc_lev_mask          = ppc_sc_tomask(17) | (0x3fff << 12) | 0x1f;
            static const uint32_t     sc_mask              = ppc_sc_tomask(17) | 0x3ffffff;

            // d
            static const uint32_t     d_bf_l_ra_si_mask = d_mask | (0x1UL << 23);
            static const uint32_t     d_bf_l_ra_ui_mask = d_bf_l_ra_si_mask;

            // x
            static const uint32_t     x_rt_ra_mask        = x_mask | (0x1fUL << 11);
            //static const uint32_t     x_rt_sr_mask     = x_mask |
            static const uint32_t     x_rt_rb_mask        = x_mask | (0x1fUL << 16);
            static const uint32_t     x_rt_mask           = x_mask | (0x1fUL << 16) | (0x1fUL << 11);
            static const uint32_t     x_rs_ra_mask        = x_rt_ra_mask;
            //static const uint32_t     x_rs_sr_mask        = x_rt_sr_mask;
            static const uint32_t     x_rs_rb_mask        = x_rt_rb_mask;
            static const uint32_t     x_rs_mask           = x_rt_mask;
            static const uint32_t     x_rs_l_mask         = x_mask | (0xfUL  << 17) | (0x1fUL << 11);
            static const uint32_t     x_bf_l_ra_rb_mask   = x_mask | (0x1UL  << 23);
            //static const uint32_t     x_bf_bfa_mask       = 
            //static const uint32_t     x_bf_w_u_mask       =
            static const uint32_t     x_bf_mask           = x_mask | (0x3UL << 21) | (0x1fUL << 16) | (0x1fUL << 11);
            //static const uint32_t     x_ct_mask           =
            static const uint32_t     x_ct_ra_rb_mask     = x_mask | (0x1UL << 25);
            static const uint32_t     x_l_ra_rb_mask      = x_mask | (0x7UL << 23);
            //static const uint32_t     x_l_rb_mask         =
            static const uint32_t     x_l_mask            = x_mask | (0x7UL << 23) | (0x1fUL << 16) | (0x1fUL << 11);
            static const uint32_t     x_bt_mask           = x_rt_mask;
            static const uint32_t     x_ra_rb_mask        = x_mask | (0x1fUL << 21);
            static const uint32_t     x_rb_mask           = x_mask | (0x1fUL << 21) | (0x1fUL << 16);
            static const uint32_t     x_all_mask          = x_mask | (0x1fUL << 21) | (0x1fUL << 16) | (0x1fUL << 11);
            static const uint32_t     x_e_mask            = x_mask | (0x1fUL << 21) | (0x1fUL << 16) | (0xfUL  << 11);
            //static const uint32_t     x_ih_mask           =
            //static const uint32_t     x_wc_mask           =
            //static const uint32_t     x_t_ra_rb_mask      =
            static const uint32_t     x_mo_mask             = x_rt_mask;

            // xl
            static const uint32_t     xl_bo_bi_bh_mask    = xl_mask | (0x7UL  << 13);
            static const uint32_t     xl_bf_bfa_mask      = xl_mask | (0x3UL  << 21) | (0x3UL  << 16) | (0x1fUL << 11);
            static const uint32_t     xl_all_mask         = xl_mask | (0x1fUL << 21) | (0x1fUL << 16) | (0x1fUL << 11);

            // xfx
            static const uint32_t     xfx_fxm_rt_mask     = xfx_fxm_mask | (0x1ffUL << 11);
            static const uint32_t     xfx_fxm_rs_fxm_mask = xfx_fxm_mask | (0x1UL   << 11);

            // xo
            static const uint32_t     xo_rt_ra_mask       = xo_mask | (0x1fUL << 11);

            // evx
            static const uint32_t     evx_rt_rb_mask      = evx_mask | (0x1fUL << 16);
            static const uint32_t     evx_rt_ra_mask      = evx_mask | (0x1fUL << 11);
            static const uint32_t     evx_bf_ra_rb_mask   = evx_mask | (0x3UL  << 21);
            static const uint32_t     evx_rt_si_mask      = evx_rt_ra_mask;


            ////////////////////////////////////////////////////////////////////////////////
            // decoder table
            ////////////////////////////////////////////////////////////////////////////////
            const ppc_opcode  decode_table[] = {
                { ppc_op_tomask        (3),               op_mask,              "twi",         &ppc_obj_subform_d_to_ra_si     },

#ifdef PPC_SPE
                { ppc_evx_tomask       (4,   512),        evx_mask,             "evaddw",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   514),        evx_mask,             "evaddiw",     &ppc_obj_subform_evx_rt_ui_rb    },
                { ppc_evx_tomask       (4,   516),        evx_mask,             "evsubfw",     &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   518),        evx_mask,             "evsubifw",    &ppc_obj_subform_evx_rt_ui_rb    },
                { ppc_evx_tomask       (4,   520),        evx_rt_ra_mask,       "evabs",       &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   521),        evx_rt_ra_mask,       "evneg",       &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   522),        evx_rt_ra_mask,       "evextsb",     &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   523),        evx_rt_ra_mask,       "evextsh",     &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   524),        evx_rt_ra_mask,       "evrndw",      &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   525),        evx_rt_ra_mask,       "evcntlzw",    &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   526),        evx_rt_ra_mask,       "evcntlsw",    &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   527),        evx_mask,             "brinc",       &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   529),        evx_mask,             "evand",       &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   530),        evx_mask,             "evandc",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   534),        evx_mask,             "evxor",       &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   535),        evx_mask,             "evor",        &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   536),        evx_mask,             "evnor",       &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   537),        evx_mask,             "eveqv",       &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   539),        evx_mask,             "evorc",       &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   542),        evx_mask,             "evnand",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   544),        evx_mask,             "evsrwu",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   545),        evx_mask,             "evsrws",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   546),        evx_mask,             "evsrwiu",     &ppc_obj_subform_evx_rt_ra_ui    },
                { ppc_evx_tomask       (4,   547),        evx_mask,             "evsrwis",     &ppc_obj_subform_evx_rt_ra_ui    },
                { ppc_evx_tomask       (4,   548),        evx_mask,             "evslw",       &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   550),        evx_mask,             "evslwi",      &ppc_obj_subform_evx_rt_ra_ui    },
                { ppc_evx_tomask       (4,   552),        evx_mask,             "evrlw",       &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   553),        evx_rt_si_mask,       "evsplati",    &ppc_obj_subform_evx_rt_si       },
                { ppc_evx_tomask       (4,   554),        evx_mask,             "evrlwi",      &ppc_obj_subform_evx_rt_ra_ui    },
                { ppc_evx_tomask       (4,   555),        evx_rt_si_mask,       "evsplatfi",   &ppc_obj_subform_evx_rt_si       },
                { ppc_evx_tomask       (4,   556),        evx_mask,             "evmergehi",   &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   557),        evx_mask,             "evmergelo",   &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   558),        evx_mask,             "evmergehilo", &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   559),        evx_mask,             "evmergelohi", &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   560),        evx_bf_ra_rb_mask,    "evcmpgtu",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   561),        evx_bf_ra_rb_mask,    "evcmpgts",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   562),        evx_bf_ra_rb_mask,    "evcmpltu",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   563),        evx_bf_ra_rb_mask,    "evcmplts",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   564),        evx_bf_ra_rb_mask,    "evcmpeq",     &ppc_obj_subform_evx_bf_ra_rb    },

                { ppc_evs_tomask       (4,    79),        evs_mask,             "evsel",       &ppc_obj_subform_evs_rt_ra_rb_bfa },

                { ppc_evx_tomask       (4,   640),        evx_mask,             "evfsadd",     &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   641),        evx_mask,             "evfssub",     &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   644),        evx_rt_ra_mask,       "evfsabs",     &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   645),        evx_rt_ra_mask,       "evfsnabs",    &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   646),        evx_rt_ra_mask,       "evfsneg",     &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   648),        evx_mask,             "evfsmul",     &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   649),        evx_mask,             "evfsdiv",     &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   652),        evx_bf_ra_rb_mask,    "evfscmpgt",   &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   653),        evx_bf_ra_rb_mask,    "evfscmplt",   &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   654),        evx_bf_ra_rb_mask,    "evfscmpeq",   &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   656),        evx_rt_rb_mask,       "evfscfui",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   657),        evx_rt_rb_mask,       "evfscfsi",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   658),        evx_rt_rb_mask,       "evfscfuf",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   659),        evx_rt_rb_mask,       "evfscfsf",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   660),        evx_rt_rb_mask,       "evfsctui",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   661),        evx_rt_rb_mask,       "evfsctsi",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   662),        evx_rt_rb_mask,       "evfsctuf",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   663),        evx_rt_rb_mask,       "evfsctsf",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   664),        evx_rt_rb_mask,       "evfsctuiz",   &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   666),        evx_rt_rb_mask,       "evfsctsiz",   &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   668),        evx_bf_ra_rb_mask,    "evfststgt",   &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   669),        evx_bf_ra_rb_mask,    "evfststlt",   &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   670),        evx_bf_ra_rb_mask,    "evfststeq",   &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   704),        evx_mask,             "efsadd",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   705),        evx_mask,             "efssub",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   708),        evx_rt_ra_mask,       "efsabs",      &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   709),        evx_rt_ra_mask,       "efsnabs",     &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   710),        evx_rt_ra_mask,       "efsneg",      &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   712),        evx_mask,             "efsmul",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   713),        evx_mask,             "efsdiv",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   716),        evx_bf_ra_rb_mask,    "efscmpgt",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   717),        evx_bf_ra_rb_mask,    "efscmplt",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   718),        evx_bf_ra_rb_mask,    "efscmpeq",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   719),        evx_rt_rb_mask,       "efscfd",      &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   720),        evx_rt_rb_mask,       "efscfui",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   721),        evx_rt_rb_mask,       "efscfsi",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   722),        evx_rt_rb_mask,       "efscfuf",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   723),        evx_rt_rb_mask,       "efscfsf",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   724),        evx_rt_rb_mask,       "efsctui",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   725),        evx_rt_rb_mask,       "efsctsi",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   726),        evx_rt_rb_mask,       "efsctuf",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   727),        evx_rt_rb_mask,       "efsctsf",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   728),        evx_rt_rb_mask,       "efsctuiz",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   730),        evx_rt_rb_mask,       "efsctsiz",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   732),        evx_bf_ra_rb_mask,    "efststgt",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   733),        evx_bf_ra_rb_mask,    "efststlt",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   734),        evx_bf_ra_rb_mask,    "efststeq",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   736),        evx_mask,             "efdadd",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   737),        evx_mask,             "efdsub",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   740),        evx_rt_ra_mask,       "efdabs",      &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   741),        evx_rt_ra_mask,       "efdnabs",     &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   742),        evx_rt_ra_mask,       "efdneg",      &ppc_obj_subform_evx_rt_ra       },
                { ppc_evx_tomask       (4,   744),        evx_mask,             "efdmul",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   745),        evx_mask,             "efddiv",      &ppc_obj_subform_evx_rt_ra_rb    },
                { ppc_evx_tomask       (4,   748),        evx_bf_ra_rb_mask,    "efdcmpgt",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   749),        evx_bf_ra_rb_mask,    "efdcmplt",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   750),        evx_bf_ra_rb_mask,    "efdcmpeq",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   751),        evx_rt_rb_mask,       "efdcfs",      &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   752),        evx_rt_rb_mask,       "efdcfui",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   753),        evx_rt_rb_mask,       "efdcfsi",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   754),        evx_rt_rb_mask,       "efdcfuf",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   755),        evx_rt_rb_mask,       "efdcfsf",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   756),        evx_rt_rb_mask,       "efdctui",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   757),        evx_rt_rb_mask,       "efdctsi",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   758),        evx_rt_rb_mask,       "efdctuf",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   759),        evx_rt_rb_mask,       "efdctsf",     &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   760),        evx_rt_rb_mask,       "efdctuiz",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   762),        evx_rt_rb_mask,       "efdctsiz",    &ppc_obj_subform_evx_rt_rb       },
                { ppc_evx_tomask       (4,   764),        evx_bf_ra_rb_mask,    "efdtstgt",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   765),        evx_bf_ra_rb_mask,    "efdtstlt",    &ppc_obj_subform_evx_bf_ra_rb    },
                { ppc_evx_tomask       (4,   766),        evx_bf_ra_rb_mask,    "efdtsteq",    &ppc_obj_subform_evx_bf_ra_rb    },

                { ppc_evx_tomask       (4,   768),        evx_mask,             "evlddx",           &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   769),        evx_mask,             "evldd",            &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   770),        evx_mask,             "evldwx",           &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   771),        evx_mask,             "evldw",            &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   772),        evx_mask,             "evldhx",           &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   773),        evx_mask,             "evldh",            &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   776),        evx_mask,             "evlhhesplatx",     &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   777),        evx_mask,             "evlhhesplat",      &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   780),        evx_mask,             "evlhhousplatx",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   781),        evx_mask,             "evlhhousplat",     &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   782),        evx_mask,             "evlhhossplatx",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   783),        evx_mask,             "evlhhossplat",     &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   784),        evx_mask,             "evlwhex",          &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   785),        evx_mask,             "evlwhe",           &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   788),        evx_mask,             "evlwhoux",         &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   789),        evx_mask,             "evlwhou",          &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   790),        evx_mask,             "evlwhosx",         &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   791),        evx_mask,             "evlwhos",          &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   792),        evx_mask,             "evlwwsplatx",      &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   793),        evx_mask,             "evlwwsplat",       &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   796),        evx_mask,             "evlwhsplatx",      &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   797),        evx_mask,             "evlwhsplat",       &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   800),        evx_mask,             "evstddx",          &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   801),        evx_mask,             "evstdd",           &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   802),        evx_mask,             "evstdwx",          &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   803),        evx_mask,             "evstdw",           &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   804),        evx_mask,             "evstdhx",          &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   805),        evx_mask,             "evstdh",           &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   816),        evx_mask,             "evstwhex",         &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   817),        evx_mask,             "evstwhe",          &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   820),        evx_mask,             "evstwhox",         &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   821),        evx_mask,             "evstwho",          &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   824),        evx_mask,             "evstwwex",         &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   825),        evx_mask,             "evstwwe",          &ppc_obj_subform_evx_rt_ra_ui  },
                { ppc_evx_tomask       (4,   828),        evx_mask,             "evstwwox",         &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,   829),        evx_mask,             "evstwwo",          &ppc_obj_subform_evx_rt_ra_ui  },

                { ppc_evx_tomask       (4,  1027),        evx_mask,             "evmhessf",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1031),        evx_mask,             "evmhossf",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1032),        evx_mask,             "evmheumi",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1033),        evx_mask,             "evmhesmi",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1035),        evx_mask,             "evmhesmf",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1036),        evx_mask,             "evmhoumi",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1037),        evx_mask,             "evmhosmi",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1039),        evx_mask,             "evmhosmf",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1059),        evx_mask,             "evmhessfa",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1063),        evx_mask,             "evmhossfa",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1064),        evx_mask,             "evmheumia",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1065),        evx_mask,             "evmhesmia",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1067),        evx_mask,             "evmhesmfa",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1068),        evx_mask,             "evmhoumia",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1069),        evx_mask,             "evmhosmia",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1071),        evx_mask,             "evmhosmfa",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1095),        evx_mask,             "evmwhssf",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1096),        evx_mask,             "evmwlumi",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1100),        evx_mask,             "evmwhumi",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1101),        evx_mask,             "evmwhsmi",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1103),        evx_mask,             "evmwhsmf",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1107),        evx_mask,             "evmwssf",     &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1112),        evx_mask,             "evmwumi",     &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1113),        evx_mask,             "evmwsmi",     &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1115),        evx_mask,             "evmwsmf",     &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1127),        evx_mask,             "evmwhssfa",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1128),        evx_mask,             "evmwlumia",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1132),        evx_mask,             "evmwhumia",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1133),        evx_mask,             "evmwhsmia",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1135),        evx_mask,             "evmwhsmfa",   &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1139),        evx_mask,             "evmwssfa",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1144),        evx_mask,             "evmwumia",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1145),        evx_mask,             "evmwsmia",    &ppc_obj_subform_evx_rt_ra_rb  },
                { ppc_evx_tomask       (4,  1147),        evx_mask,             "evmwsmfa",    &ppc_obj_subform_evx_rt_ra_rb  },

                { ppc_evx_tomask       (4,  1216),       evx_mask,              "evaddusiaaw",      &ppc_obj_subform_evx_rt_ra  },
                { ppc_evx_tomask       (4,  1217),       evx_mask,              "evaddssiaaw",      &ppc_obj_subform_evx_rt_ra  },
                { ppc_evx_tomask       (4,  1218),       evx_mask,              "evsubfusiaaw",     &ppc_obj_subform_evx_rt_ra  }, 
                { ppc_evx_tomask       (4,  1219),       evx_mask,              "evsubfssiaaw",     &ppc_obj_subform_evx_rt_ra  },
                { ppc_evx_tomask       (4,  1220),       evx_mask,              "evmra",            &ppc_obj_subform_evx_rt_ra  },
                { ppc_evx_tomask       (4,  1222),       evx_mask,              "evdivws",          &ppc_obj_subform_evx_rt_ra  },
                { ppc_evx_tomask       (4,  1223),       evx_mask,              "evdivwu",          &ppc_obj_subform_evx_rt_ra  },
                { ppc_evx_tomask       (4,  1224),       evx_mask,              "evaddumiaaw",      &ppc_obj_subform_evx_rt_ra  },
                { ppc_evx_tomask       (4,  1225),       evx_mask,              "evaddsmiaaw",      &ppc_obj_subform_evx_rt_ra  },
                { ppc_evx_tomask       (4,  1226),       evx_mask,              "evsubfumiaaw",     &ppc_obj_subform_evx_rt_ra  },
                { ppc_evx_tomask       (4,  1227),       evx_mask,              "evsubfsmiaaw",     &ppc_obj_subform_evx_rt_ra  },

                { ppc_evx_tomask       (4,  1280),       evx_mask,              "evmheusiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1281),       evx_mask,              "evmhessiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1283),       evx_mask,              "evmhessfaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1284),       evx_mask,              "evmhousiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1285),       evx_mask,              "evmhossiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1287),       evx_mask,              "evmhossfaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1288),       evx_mask,              "evmheumiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1289),       evx_mask,              "evmhesmiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1291),       evx_mask,              "evmhesmfaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1292),       evx_mask,              "evmhoumiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1293),       evx_mask,              "evmhosmiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1295),       evx_mask,              "evmhosmfaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1320),       evx_mask,              "evmhegumiaa",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1321),       evx_mask,              "evmhegsmiaa",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1323),       evx_mask,              "evmhegsmfaa",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1324),       evx_mask,              "evmhogumiaa",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1325),       evx_mask,              "evmhogsmiaa",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1327),       evx_mask,              "evmhogsmfaa",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1344),       evx_mask,              "evmwlusiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1352),       evx_mask,              "evmwlumiaaw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1363),       evx_mask,              "evmwssfaa",        &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1368),       evx_mask,              "evmwumiaa",        &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1369),       evx_mask,              "evmwsmiaa",        &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1371),       evx_mask,              "evmwsmfaa",        &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1408),       evx_mask,              "evmheusianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1409),       evx_mask,              "evmhessianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1411),       evx_mask,              "evmhessfanw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1412),       evx_mask,              "evmhousianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1413),       evx_mask,              "evmhossianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1415),       evx_mask,              "evmhossfanw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1416),       evx_mask,              "evmheumianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1417),       evx_mask,              "evmhesmianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1419),       evx_mask,              "evmhesmfanw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1420),       evx_mask,              "evmhoumianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1421),       evx_mask,              "evmhosmianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1423),       evx_mask,              "evmhosmfanw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1448),       evx_mask,              "evmhegumian",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1449),       evx_mask,              "evmhegsmian",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1451),       evx_mask,              "evmhegsmfan",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1452),       evx_mask,              "evmhogumian",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1453),       evx_mask,              "evmhogsmian",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1455),       evx_mask,              "evmhogsmfan",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1472),       evx_mask,              "evmwlusianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1480),       evx_mask,              "evmwlumianw",      &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1491),       evx_mask,              "evmwssfan",        &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1496),       evx_mask,              "evmwumian",        &ppc_obj_subform_evx_rt_ra_rb   },
                { ppc_evx_tomask       (4,  1497),       evx_mask,              "evmwsmian",        &ppc_obj_subform_evx_rt_ra_rb   },
#endif

                { ppc_op_tomask        (7),               op_mask,              "mulli",       &ppc_obj_subform_d_rt_ra_si     },
                { ppc_op_tomask        (8),               op_mask,              "subfic",      &ppc_obj_subform_d_rt_ra_si     },
                { ppc_op_tomask        (10),              d_bf_l_ra_ui_mask,    "cmpli",       &ppc_obj_subform_d_bf_l_ra_ui   },
                { ppc_op_tomask        (11),              d_bf_l_ra_si_mask,    "cmpi",        &ppc_obj_subform_d_bf_l_ra_si   },
                { ppc_op_tomask        (12),              op_mask,              "addic",       &ppc_obj_subform_d_rt_ra_si     },
                { ppc_op_tomask        (13),              op_mask,              "addic.",      &ppc_obj_subform_d_rt_ra_si     },
                { ppc_op_tomask        (14),              op_mask,              "addi",        &ppc_obj_subform_d_rt_ra_si     },
                { ppc_op_tomask        (15),              op_mask,              "addis",       &ppc_obj_subform_d_rt_ra_si     },

                { ppc_b_tomask         (16,    0, 0),     b_mask,               "bc",          &ppc_obj_subform_b_bo_bi_bd     },
                { ppc_b_tomask         (16,    0, 1),     b_mask,               "bcl",         &ppc_obj_subform_b_bo_bi_bd     },
                { ppc_b_tomask         (16,    1, 0),     b_mask,               "bca",         &ppc_obj_subform_b_bo_bi_bd     },
                { ppc_b_tomask         (16,    1, 1),     b_mask,               "bcla",        &ppc_obj_subform_b_bo_bi_bd     },

                { ppc_sc_tomask        (17),              sc_mask,              "sc",          &ppc_obj_subform_sc_lev         },

                { ppc_i_tomask         (18,    0, 0),     i_mask,               "b",           &ppc_obj_subform_i_li           },
                { ppc_i_tomask         (18,    0, 1),     i_mask,               "bl",          &ppc_obj_subform_i_li           },
                { ppc_i_tomask         (18,    1, 0),     i_mask,               "ba",          &ppc_obj_subform_i_li           },
                { ppc_i_tomask         (18,    1, 1),     i_mask,               "bla",         &ppc_obj_subform_i_li           },

                { ppc_xl_tomask        (19,    0, 0),     xl_bf_bfa_mask,       "mcrf",        &ppc_obj_subform_xl_bf_bfa      },
                { ppc_xl_tomask        (19,   16, 0),     xl_bo_bi_bh_mask,     "bclr",        &ppc_obj_subform_xl_bo_bi_bh    },
                { ppc_xl_tomask        (19,   16, 1),     xl_bo_bi_bh_mask,     "bclrl",       &ppc_obj_subform_xl_bo_bi_bh    },
                { ppc_xl_tomask        (19,   33, 0),     xl_mask,              "crnor",       &ppc_obj_subform_xl_bt_ba_bb    },
                { ppc_xl_tomask        (19,   38, 0),     xl_all_mask,          "rfmci",       &ppc_obj_subform_xl             },
                { ppc_xl_tomask        (19,   50, 0),     xl_all_mask,          "rfi",         &ppc_obj_subform_xl             },
                { ppc_xl_tomask        (19,   51, 0),     xl_all_mask,          "rfci",        &ppc_obj_subform_xl             },
                { ppc_xl_tomask        (19,  129, 0),     xl_mask,              "crandc",      &ppc_obj_subform_xl_bt_ba_bb    },
                { ppc_xl_tomask        (19,  150, 0),     xl_all_mask,          "isync",       &ppc_obj_subform_xl             },
                { ppc_xl_tomask        (19,  193, 0),     xl_mask,              "crxor",       &ppc_obj_subform_xl_bt_ba_bb    },
                { ppc_xl_tomask        (19,  225, 0),     xl_mask,              "crnand",      &ppc_obj_subform_xl_bt_ba_bb    },
                { ppc_xl_tomask        (19,  257, 0),     xl_mask,              "crand",       &ppc_obj_subform_xl_bt_ba_bb    },
                { ppc_xl_tomask        (19,  289, 0),     xl_mask,              "creqv",       &ppc_obj_subform_xl_bt_ba_bb    },
                { ppc_xl_tomask        (19,  417, 0),     xl_mask,              "crorc",       &ppc_obj_subform_xl_bt_ba_bb    },
                { ppc_xl_tomask        (19,  449, 0),     xl_mask,              "cror",        &ppc_obj_subform_xl_bt_ba_bb    },
                { ppc_xl_tomask        (19,  528, 0),     xl_mask,              "bcctr",       &ppc_obj_subform_xl_bo_bi_bh    },
                { ppc_xl_tomask        (19,  528, 1),     xl_mask,              "bcctrl",      &ppc_obj_subform_xl_bo_bi_bh    },

                { ppc_m_tomask         (20,  0),          m_mask,               "rlwimi",      &ppc_obj_subform_m_rs_ra_sh_mb_me    },
                { ppc_m_tomask         (20,  1),          m_mask,               "rlwimi.",     &ppc_obj_subform_m_rs_ra_sh_mb_me    },
                { ppc_m_tomask         (21,  0),          m_mask,               "rlwinm",      &ppc_obj_subform_m_rs_ra_sh_mb_me    },
                { ppc_m_tomask         (21,  1),          m_mask,               "rlwinm.",     &ppc_obj_subform_m_rs_ra_sh_mb_me    },
                { ppc_m_tomask         (23,  0),          m_mask,               "rlwnm",       &ppc_obj_subform_m_rs_ra_rb_mb_me    },
                { ppc_m_tomask         (23,  1),          m_mask,               "rlwnm.",      &ppc_obj_subform_m_rs_ra_rb_mb_me    },
               
                { ppc_op_tomask        (24),              op_mask,              "ori",         &ppc_obj_subform_d_rs_ra_ui     },
                { ppc_op_tomask        (25),              op_mask,              "oris",        &ppc_obj_subform_d_rs_ra_ui     },
                { ppc_op_tomask        (26),              op_mask,              "xori",        &ppc_obj_subform_d_rs_ra_ui     },
                { ppc_op_tomask        (27),              op_mask,              "xoris",       &ppc_obj_subform_d_rs_ra_ui     },
                { ppc_op_tomask        (28),              op_mask,              "andi.",       &ppc_obj_subform_d_rs_ra_ui     },
                { ppc_op_tomask        (29),              op_mask,              "andis.",      &ppc_obj_subform_d_rs_ra_ui     },

                { ppc_x_tomask         (31,    0, 0),     d_bf_l_ra_rb_mask,    "cmp",         &ppc_obj_subform_x_bf_l_ra_rb   },
                { ppc_x_tomask         (31,    4, 0),     x_mask,               "tw",          &ppc_obj_subform_x_to_ra_rb     },
               
                { ppc_xo_tomask        (31,    8, 0, 0),  xo_mask,              "subfc",       &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,    8, 0, 1),  xo_mask,              "subfc.",      &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,   10, 0, 0),  xo_mask,              "addc",        &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,   10, 0, 1),  xo_mask,              "addc.",       &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,   11, 0, 0),  xo_mask,              "mulhwu",      &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,   11, 0, 1),  xo_mask,              "mulhwu.",     &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_xfx_fxm_tomask   (31,   19, 0),     xfx_fxm_rt_mask,      "mfcr",        &ppc_obj_subform_xfx_rt         },

                { ppc_x_tomask         (31,   20, 0),     x_mask,               "lwarx",       &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,   22, 0),     x_ct_ra_rb_mask,      "icbt",        &ppc_obj_subform_x_ct_ra_rb     },
                { ppc_x_tomask         (31,   23, 0),     x_mask,               "lwzx",        &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,   24, 0),     x_mask,               "slw",         &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,   24, 1),     x_mask,               "slw.",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,   26, 0),     x_rs_ra_mask,         "cntlzw",      &ppc_obj_subform_x_rs_ra        },
                { ppc_x_tomask         (31,   26, 1),     x_rs_ra_mask,         "cntlzw.",     &ppc_obj_subform_x_rs_ra        },
                { ppc_x_tomask         (31,   28, 0),     x_mask,               "and",         &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,   28, 1),     x_mask,               "and.",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,   32, 0),     x_bf_l_ra_rb_mask,    "cmpl",        &ppc_obj_subform_x_bf_l_ra_rb   },

                { ppc_a_tomask         (31,   15),        a_mask,               "isel",        &ppc_obj_subform_a_rt_ra_rb_bc  },
                
                { ppc_xo_tomask        (31,   40, 0, 0),  xo_mask,              "subf",        &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,   40, 0, 1),  xo_mask,              "subf.",       &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,   54),        x_ra_rb_mask,         "dcbst",       &ppc_obj_subform_x_ra_rb        },
                { ppc_x_tomask         (31,   55),        x_mask,               "lwzux",       &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,   60, 0),     x_mask,               "andc",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,   60, 1),     x_mask,               "andc.",       &ppc_obj_subform_x_rs_ra_rb     },

                { ppc_xo_tomask        (31,   75, 0, 0),  xo_mask,              "mulhw",       &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_xo_tomask        (31,   75, 0, 1),  xo_mask,              "mulhw.",      &ppc_obj_subform_x_rt_ra_rb     },

                { ppc_x_tomask         (31,   83),        x_rt_mask,            "mfmsr",       &ppc_obj_subform_x_rt           },
                { ppc_x_tomask         (31,   86),        x_l_ra_rb_mask,       "dcbf",        &ppc_obj_subform_x_l_ra_rb      },
                { ppc_x_tomask         (31,   87),        x_mask,               "lbzx",        &ppc_obj_subform_x_rt_ra_rb     },

                { ppc_xo_tomask        (31,  104, 0, 0),  xo_rt_ra_mask,        "neg",         &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  104, 0, 1),  xo_rt_ra_mask,        "neg.",        &ppc_obj_subform_xo_rt_ra       },

                { ppc_x_tomask         (31,  119),        x_mask,               "lbzux",       &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,  124, 0),     x_mask,               "nor",         &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  124, 1),     x_mask,               "nor.",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  131),        x_rs_mask,            "wrtee",       &ppc_obj_subform_x_rs           },
                { ppc_x_tomask         (31,  134),        x_ct_ra_rb_mask,      "dcbtstls",    &ppc_obj_subform_x_ct_ra_rb     },

                { ppc_xo_tomask        (31,  136, 0, 0),  xo_mask,              "subfe",       &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  136, 0, 1),  xo_mask,              "subfe.",      &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  138, 0, 0),  xo_mask,              "adde",        &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  138, 0, 1),  xo_mask,              "adde.",       &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_xfx_fxm_tomask   (31,  144, 0),     xfx_fxm_rs_fxm_mask,  "mtcrf",       &ppc_obj_subform_xfx_rs_fxm     },

                { ppc_x_tomask         (31,  146),        x_rs_l_mask,          "mtmsr",       &ppc_obj_subform_x_rs_l         },
                { ppc_x_tomask         (31,  150, 1),     x_mask,               "stwcx.",      &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  151),        x_mask,               "stwx",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  163),        x_e_mask,             "wrteei",      &ppc_obj_subform_x_e            },
                { ppc_x_tomask         (31,  166),        x_ct_ra_rb_mask,      "dcbtls",      &ppc_obj_subform_x_ct_ra_rb     },
                { ppc_x_tomask         (31,  183),        x_mask,               "stwux",       &ppc_obj_subform_x_rs_ra_rb     },

                { ppc_xo_tomask        (31,  200, 0, 0),  xo_rt_ra_mask,        "subfze",      &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  200, 0, 1),  xo_rt_ra_mask,        "subfze.",     &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  202, 0, 0),  xo_rt_ra_mask,        "addze",       &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  202, 0, 1),  xo_rt_ra_mask,        "addze.",      &ppc_obj_subform_xo_rt_ra       },

                { ppc_x_tomask         (31,  215),        x_mask,               "stbx",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  230),        x_ct_ra_rb_mask,      "icblc",       &ppc_obj_subform_x_ct_ra_rb     },

                { ppc_xo_tomask        (31,  232, 0, 0),  xo_rt_ra_mask,        "subfme",      &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  232, 0, 1),  xo_rt_ra_mask,        "subfme.",     &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  234, 0, 0),  xo_rt_ra_mask,        "addme",       &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  234, 0, 1),  xo_rt_ra_mask,        "addme.",      &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  235, 0, 0),  xo_mask,              "mullw",       &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  235, 0, 1),  xo_mask,              "mullw.",      &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,  246),        x_mask,               "dcbtst",      &ppc_obj_subform_x_ct_ra_rb     },
                { ppc_x_tomask         (31,  247),        x_mask,               "stbux",       &ppc_obj_subform_x_rs_ra_rb     },

                { ppc_xo_tomask        (31,  266, 0, 0),  xo_mask,              "add",         &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  266, 0, 1),  xo_mask,              "add.",        &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,  278),        x_mask,               "dcbt",        &ppc_obj_subform_x_ct_ra_rb     },
                { ppc_x_tomask         (31,  279),        x_mask,               "lhzx",        &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,  284, 0),     x_mask,               "eqv",         &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  284, 1),     x_mask,               "eqv.",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  311),        x_mask,               "lhzux",       &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,  316, 0),     x_mask,               "xor",         &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  316, 1),     x_mask,               "xor.",        &ppc_obj_subform_x_rs_ra_rb     },

                { ppc_xfx_tomask       (31,  334),        xfx_mask,             "mfpmr",       &ppc_obj_subform_xfx_rt_pmr     },
                { ppc_xfx_tomask       (31,  339),        xfx_mask,             "mfspr",       &ppc_obj_subform_xfx_rt_spr     },

                { ppc_x_tomask         (31,  343),        x_mask,               "lhax",        &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,  375),        x_mask,               "lhaux",       &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,  390),        x_ct_ra_rb_mask,      "dcblc",       &ppc_obj_subform_x_ct_ra_rb     },
                { ppc_x_tomask         (31,  407),        x_mask,               "sthx",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  412, 0),     x_mask,               "orc",         &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  412, 1),     x_mask,               "orc.",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  439),        x_mask,               "sthux",       &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  444, 0),     x_mask,               "or",          &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  444, 1),     x_mask,               "or.",         &ppc_obj_subform_x_rs_ra_rb     },

                { ppc_xo_tomask        (31,  459, 0, 0),  xo_mask,              "divwu",       &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  459, 0, 1),  xo_mask,              "divwu.",      &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_xfx_tomask       (31,  462),        xfx_mask,             "mtpmr",       &ppc_obj_subform_xfx_rs_pmr     },
                { ppc_xfx_tomask       (31,  467),        xfx_mask,             "mtspr",       &ppc_obj_subform_xfx_rs_spr     },

                { ppc_x_tomask         (31,  470),        x_ra_rb_mask,         "dcbi",        &ppc_obj_subform_x_ra_rb        },
                { ppc_x_tomask         (31,  476, 0),     x_mask,               "nand",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  476, 1),     x_mask,               "nand.",       &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  486),        x_ct_ra_rb_mask,      "icbtls",      &ppc_obj_subform_x_ct_ra_rb     },

                { ppc_xo_tomask        (31,  491, 0, 0),  xo_mask,              "divw",        &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  491, 0, 1),  xo_mask,              "divw.",       &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,  512),        x_bf_mask,            "mcrxr",       &ppc_obj_subform_x_bf           },

                // FIXME : ADD bblels

                { ppc_xo_tomask        (31,    8, 1, 0),  xo_mask,              "subfco",      &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,    8, 1, 1),  xo_mask,              "subfco.",     &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,   10, 1, 0),  xo_mask,              "addco",       &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,   10, 1, 1),  xo_mask,              "addco.",      &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,  534),        x_mask,               "lwbrx",       &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,  536, 0),     x_mask,               "srw",         &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  536, 1),     x_mask,               "srw.",        &ppc_obj_subform_x_rs_ra_rb     },

                // FIXME : ADD bbelr

                { ppc_xo_tomask        (31,   40, 1, 0),  xo_mask,              "subfo",       &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,   40, 1, 1),  xo_mask,              "subfo.",      &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,  566),        x_all_mask,           "tlbsync",     &ppc_obj_subform_x              },
                { ppc_x_tomask         (31,  598),        x_l_mask,             "msync",       &ppc_obj_subform_x_l            },

                { ppc_xo_tomask        (31,  104, 1, 0),  xo_rt_ra_mask,        "nego",        &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  104, 1, 1),  xo_rt_ra_mask,        "nego.",       &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  136, 1, 0),  xo_mask,              "subfeo",      &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  136, 1, 1),  xo_mask,              "subfeo.",     &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  138, 1, 0),  xo_mask,              "addeo",       &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  138, 1, 1),  xo_mask,              "addeo.",      &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,  662),        x_mask,               "stwbrx",      &ppc_obj_subform_x_rs_ra_rb     },

                { ppc_xo_tomask        (31,  200, 1, 0),  xo_rt_ra_mask,        "subfzeo",     &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  200, 1, 1),  xo_rt_ra_mask,        "subfzeo.",    &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  202, 1, 0),  xo_rt_ra_mask,        "addzeo",      &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  202, 1, 1),  xo_rt_ra_mask,        "addzeo.",     &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  232, 1, 0),  xo_rt_ra_mask,        "subfmeo",     &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  232, 1, 1),  xo_rt_ra_mask,        "subfmeo.",    &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  234, 1, 0),  xo_rt_ra_mask,        "addmeo",      &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  234, 1, 1),  xo_rt_ra_mask,        "addmeo.",     &ppc_obj_subform_xo_rt_ra       },
                { ppc_xo_tomask        (31,  235, 1, 0),  xo_mask,              "mullwo",      &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  235, 1, 1),  xo_mask,              "mullwo.",     &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,  758),        x_ra_rb_mask,         "dcba",        &ppc_obj_subform_x_ra_rb        },

                { ppc_xo_tomask        (31,  266, 1, 0),  xo_mask,              "addo",        &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  266, 1, 1),  xo_mask,              "addo.",       &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,  786),        x_ra_rb_mask,         "tlbivax",     &ppc_obj_subform_x_ra_rb        },
                { ppc_x_tomask         (31,  790),        x_mask,               "lhbrx",       &ppc_obj_subform_x_rt_ra_rb     },
                { ppc_x_tomask         (31,  792, 0),     x_mask,               "sraw",        &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  792, 1),     x_mask,               "sraw.",       &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  824, 0),     x_mask,               "srawi",       &ppc_obj_subform_x_rs_ra_sh     },
                { ppc_x_tomask         (31,  824, 1),     x_mask,               "srawi.",      &ppc_obj_subform_x_rs_ra_sh     },
                { ppc_x_tomask         (31,  854),        x_mo_mask,            "mbar",        &ppc_obj_subform_x_mo           },
                { ppc_x_tomask         (31,  914),        x_ra_rb_mask,         "tlbsx",       &ppc_obj_subform_x_ra_rb        },
                { ppc_x_tomask         (31,  918),        x_mask,               "sthbrx",      &ppc_obj_subform_x_rs_ra_rb     },
                { ppc_x_tomask         (31,  922, 0),     x_rs_ra_mask,         "extsh",       &ppc_obj_subform_x_rs_ra        },
                { ppc_x_tomask         (31,  922, 1),     x_rs_ra_mask,         "extsh.",      &ppc_obj_subform_x_rs_ra        },
                { ppc_x_tomask         (31,  946),        x_all_mask,           "tlbre",       &ppc_obj_subform_x              },
                { ppc_x_tomask         (31,  954, 0),     x_rs_ra_mask,         "extsb",       &ppc_obj_subform_x_rs_ra        },
                { ppc_x_tomask         (31,  954, 1),     x_rs_ra_mask,         "extsb.",      &ppc_obj_subform_x_rs_ra        },

                { ppc_xo_tomask        (31,  459, 1, 0),  xo_mask,              "divwuo",      &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  459, 1, 1),  xo_mask,              "divwuo.",     &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31,  978),        x_all_mask,           "tlbwe",       &ppc_obj_subform_x              },
                { ppc_x_tomask         (31,  982),        x_ra_rb_mask,         "icbi",        &ppc_obj_subform_x_ra_rb        },

                { ppc_xo_tomask        (31,  491, 1, 0),  xo_mask,              "divwo",       &ppc_obj_subform_xo_rt_ra_rb    },
                { ppc_xo_tomask        (31,  491, 1, 1),  xo_mask,              "divwo.",      &ppc_obj_subform_xo_rt_ra_rb    },

                { ppc_x_tomask         (31, 1014),        x_ra_rb_mask,         "dcbz",        &ppc_obj_subform_x_ra_rb        },

                { ppc_op_tomask        (32),              op_mask,              "lwz",         &ppc_obj_subform_d_rt_ra_d      },
                { ppc_op_tomask        (33),              op_mask,              "lwzu",        &ppc_obj_subform_d_rt_ra_d      },
                { ppc_op_tomask        (34),              op_mask,              "lbz",         &ppc_obj_subform_d_rt_ra_d      },
                { ppc_op_tomask        (35),              op_mask,              "lbzu",        &ppc_obj_subform_d_rt_ra_d      },
                { ppc_op_tomask        (36),              op_mask,              "stw",         &ppc_obj_subform_d_rs_ra_d      },
                { ppc_op_tomask        (37),              op_mask,              "stwu",        &ppc_obj_subform_d_rs_ra_d      },
                { ppc_op_tomask        (38),              op_mask,              "stb",         &ppc_obj_subform_d_rs_ra_d      },
                { ppc_op_tomask        (39),              op_mask,              "stbu",        &ppc_obj_subform_d_rs_ra_d      },
                { ppc_op_tomask        (40),              op_mask,              "lhz",         &ppc_obj_subform_d_rt_ra_d      },
                { ppc_op_tomask        (41),              op_mask,              "lhzu",        &ppc_obj_subform_d_rt_ra_d      },
                { ppc_op_tomask        (42),              op_mask,              "lha",         &ppc_obj_subform_d_rt_ra_d      },
                { ppc_op_tomask        (43),              op_mask,              "lhau",        &ppc_obj_subform_d_rt_ra_d      },
                { ppc_op_tomask        (44),              op_mask,              "sth",         &ppc_obj_subform_d_rs_ra_d      },
                { ppc_op_tomask        (45),              op_mask,              "sthu",        &ppc_obj_subform_d_rs_ra_d      },
                { ppc_op_tomask        (46),              op_mask,              "lmw",         &ppc_obj_subform_d_rt_ra_d      },
                { ppc_op_tomask        (47),              op_mask,              "stmw",        &ppc_obj_subform_d_rs_ra_d      },

                // END TABLE
            };

            static const size_t decode_table_size = sizeof(decode_table)/sizeof(ppc_opcode);
        } // end details

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //
        //
        // decoder class
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // instruction to primary opcode 
        uint32_t insn_to_opc(uint32_t insn) { return (insn >> 26) & 0x3f; }

        class ppcdis{
            public:
            // constructor
            ppcdis(){}
        
            // Disassemble a 32 bit opcode & print it
            void print_disasm(uint32_t insn, uint64_t pc=0, int le=0){
                 struct details::ppc_opcode *table_entry;
                 size_t  i = 0;

                 // We reverse endianness if LITTLE endian specified
                 if (le) { insn = (((insn >>  0) & 0xff) << 24) | (((insn >>  8) & 0xff) << 16) | (((insn >> 16) & 0xff) <<  8) | (((insn >> 24) & 0xff) <<  0) ; }

                 // Get the table entry
                 for(i=0; i<details::decode_table_size; i++){
                     if((details::decode_table[i].mask & insn) == details::decode_table[i].opcode){ break; }
                 }

                 // No match found
                 if(i == details::decode_table_size){
                     std::cout << ".long " << details::TSH(insn) << std::endl;
                     return;
                 }

                 // Get table entry
                 table_entry = const_cast<struct details::ppc_opcode*>(&details::decode_table[i]);

                 // print string form
                 std::cout << table_entry->to_str(insn) << std::endl;
            }

        };
    }
}
