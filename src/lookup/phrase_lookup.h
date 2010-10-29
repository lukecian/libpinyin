/* 
 *  libpinyin
 *  Library to deal with pinyin.
 *  
 *  Copyright (C) 2006-2007 Peng Wu
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef PHRASE_LOOKUP_H
#define PHRASE_LOOKUP_H

#include "novel_types.h"
#include "lookup.h"

/** @file phrase_lookup.h
 *  @brief the definitions of phrase lookup related classes and structs.
 */

class PhraseLookup{
protected:
    //saved varibles
    novel::PhraseLargeTable * m_phrase_table;
    novel::FacadePhraseIndex * m_phrase_index;
    novel::Bigram * m_bigram;

    //internal step data structure
    GPtrArray * m_steps_index;
    /* Array of LookupStepIndex */
    GPtrArray * m_steps_content;
    /* Array of LookupStepContent */

    /* Saved sentence */
    int m_sentence_length;
    utf16_t * m_sentence;

protected:
    /* Explicitly search the next phrase,
     *  to avoid double phrase lookup as the next token has only one.
     */
    bool search_unigram(int nstep, phrase_token_t token);
    bool search_bigram(int nstep, phrase_token_t token);

    bool unigram_gen_next_step(int nstep, lookup_value_t * cur_step, phrase_token_t token);
    bool bigram_gen_next_step(int nstep, lookup_value_t * cur_step, phrase_token_t token, gfloat bigram_poss);

    bool save_next_step(int next_step_pos, lookup_value_t * cur_step, lookup_value_t * next_step);

    bool final_step(MatchResults & results);
public:
    /* Note: this method only accepts the characters in phrase large table. */
    bool get_best_match(int sentence_length, utf16_t sentence[], MatchResults & results);

    bool convert_to_utf8(MatchResults results, /* out */ char * & result_string);
};

#endif
