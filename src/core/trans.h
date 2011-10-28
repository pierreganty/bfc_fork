/******************************************************************************
  Synopsis		[Transition objects.]

  Author		[Alexander Kaiser]

(C) 2011 Alexander Kaiser, University of Oxford, United Kingdom

All rights reserved. Redistribution and use in source and binary forms, with
or without modification, are permitted provided that the following
conditions are met:

  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

  3. All advertising materials mentioning features or use of this software
     must display the following acknowledgement:

     This product includes software developed by Alexander Kaiser, 
     University of Oxford, United Kingdom and its contributors.

  4. Neither the name of the University nor the names of its contributors
     may be used to endorse or promote products derived from this software
     without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS `AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#ifndef TRANS_H
#define TRANS_H

enum trans_type
{
	thread_transition, 
	transfer_transition, 
	spawn_transition, 
	dummy
};

enum trans_dir_t
{
	unset,
	hor,
	nonhor
};

struct Transition
{	
	Thread_State	source;
	Thread_State	target;
	trans_type		type;
	int				id;
	trans_dir_t		dir;
	Transition(const Thread_State& s = Thread_State(0,0), const Thread_State& t = Thread_State(0,0), const trans_type& ty = dummy, int i = -1, trans_dir_t d = unset)
		: source(s), target(t), type(ty), id(i), dir(d) { }
};

bool operator < (const Transition& t1, const Transition& t2) 
{
	if(t1.source < t2.source) return 1;
	if(t2.source < t1.source) return 0;
	if(t1.target < t2.target) return 1;
	if(t2.target < t1.target) return 0;
	return t1.type < t2.type;
}

bool operator ==(const Transition& t1, const Transition& t2) 
{
	return t1.source == t2.source && t1.target == t2.target && t1.type == t2.type;
}

inline ostream& operator << (ostream& out, const Transition& t) 
{ 
	if(!out.rdbuf()) return out;
	out << "(" << t.source << ")" << (t.type==thread_transition?"->":"~>") << "(" << t.target << ")";
	return out;
}

inline ostream& extended_print(ostream& out, const Transition& t) 
{ 
	out << "[" << t.id << "]: " << "(" << t.source << ")" << (t.type==thread_transition?"->":"~>") << "(" << t.target << ")";
	return out;
}

#endif