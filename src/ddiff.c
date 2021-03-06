/*** ddiff.c -- perform simple date arithmetic, date minus date
 *
 * Copyright (C) 2011-2012 Sebastian Freundt
 *
 * Author:  Sebastian Freundt <freundt@ga-group.nl>
 *
 * This file is part of dateutils.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author nor the names of any contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/
#if defined HAVE_CONFIG_H
# include "config.h"
#endif	/* HAVE_CONFIG_H */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>

#include "dt-core.h"
#include "dt-io.h"
#include "prchunk.h"

#if !defined UNUSED
# define UNUSED(_x)	__attribute__((unused)) _x
#endif	/* !UNUSED */

typedef union {
	unsigned int flags;
	struct {
		unsigned int has_year:1;
		unsigned int has_mon:1;
		unsigned int has_week:1;
		unsigned int has_day:1;
		unsigned int has_biz:1;

		unsigned int has_hour:1;
		unsigned int has_min:1;
		unsigned int has_sec:1;
		unsigned int has_nano:1;

		unsigned int has_tai:1;
	};
} durfmt_t;


static durfmt_t
determine_durfmt(const char *fmt)
{
	durfmt_t res = {0};
	dt_dtyp_t special;

	if (fmt == NULL) {
		/* decide later on */
		;
	} else if (UNLIKELY((special = __trans_dfmt_special(fmt)) != DT_DUNK)) {
		switch (special) {
		default:
		case DT_DUNK:
			break;
		case DT_YMD:
			res.has_year = 1;
			res.has_mon = 1;
			res.has_day = 1;
			break;
		case DT_YMCW:
			res.has_year = 1;
			res.has_mon = 1;
			res.has_week = 1;
			res.has_day = 1;
			break;
		case DT_BIZDA:
			res.has_year = 1;
			res.has_mon = 1;
			res.has_day = 1;
			res.has_biz = 1;
			break;
		case DT_BIZSI:
			res.has_day = 1;
			res.has_biz = 1;
			break;
		case DT_YWD:
			res.has_year = 1;
			res.has_week = 1;
			res.has_day = 1;
			break;
		case DT_YD:
			res.has_year = 1;
			res.has_day = 1;
			break;
		}

		/* all special types have %0H:%0M:%0S */
		res.has_hour = 1;
		res.has_min = 1;
		res.has_sec = 1;
	} else {
		/* go through the fmt specs */
		for (const char *fp = fmt; *fp;) {
			const char *fp_sav = fp;
			struct dt_spec_s spec = __tok_spec(fp_sav, &fp);

			switch (spec.spfl) {
			case DT_SPFL_UNK:
			default:
				/* nothing changes */
				break;
			case DT_SPFL_N_YEAR:
				res.has_year = 1;
				break;
			case DT_SPFL_N_MON:
			case DT_SPFL_S_MON:
				res.has_mon = 1;
				break;
			case DT_SPFL_N_DCNT_MON:
				if (spec.bizda) {
					res.has_biz = 1;
				}
			case DT_SPFL_N_DSTD:
			case DT_SPFL_N_DCNT_YEAR:
				res.has_day = 1;
				break;
			case DT_SPFL_N_WCNT_MON:
			case DT_SPFL_N_WCNT_YEAR:
			case DT_SPFL_N_DCNT_WEEK:
			case DT_SPFL_S_WDAY:
				res.has_week = 1;
				break;

			case DT_SPFL_N_TSTD:
			case DT_SPFL_N_SEC:
				if (spec.tai) {
					res.has_tai = 1;
				}
				res.has_sec = 1;
				break;
			case DT_SPFL_N_HOUR:
				res.has_hour = 1;
				break;
			case DT_SPFL_N_MIN:
				res.has_min = 1;
				break;
			case DT_SPFL_N_NANO:
				res.has_nano = 1;
				break;
			}
		}
	}
	return res;
}

static dt_dttyp_t
determine_durtype(struct dt_dt_s d1, struct dt_dt_s d2, durfmt_t f)
{
	/* the type-multiplication table looks like:
	 *
	 * -   D   T   DT
	 * D   d   x   d
	 * T   x   t   x
	 * DT  d   x   s
	 *
	 * where d means a ddur type, t a tdur type and s is DT_SEXY */

	if (UNLIKELY(dt_sandwich_only_t_p(d1) && dt_sandwich_only_t_p(d2))) {
		/* time only duration */
		;
	} else if (dt_sandwich_only_t_p(d1) || dt_sandwich_only_t_p(d2)) {
		/* isn't defined */
		return (dt_dttyp_t)DT_UNK;
	} else if (f.has_week && f.has_mon) {
		return (dt_dttyp_t)DT_YMCW;
	} else if (f.has_week && f.has_year) {
		return (dt_dttyp_t)DT_YWD;
	} else if (f.has_mon) {
		return (dt_dttyp_t)DT_YMD;
	} else if (f.has_year && f.has_day) {
		return (dt_dttyp_t)DT_YD;
	} else if (f.has_day && f.has_biz) {
		return (dt_dttyp_t)DT_BIZSI;
	} else if (f.has_year) {
		return (dt_dttyp_t)DT_MD;
	} else if (dt_sandwich_only_d_p(d1) || dt_sandwich_only_d_p(d2)) {
		/* default date-only type */
		return (dt_dttyp_t)DT_DAISY;
	} else if (UNLIKELY(f.has_tai)) {
		/* we has tais */
		return (dt_dttyp_t)DT_SEXYTAI;
	}
	return (dt_dttyp_t)DT_SEXY;
}


/* printers */
static void
__attribute__((format(printf, 2, 3)))
error(int eno, const char *fmt, ...)
{
	va_list vap;
	va_start(vap, fmt);
	fputs("ddiff: ", stderr);
	vfprintf(stderr, fmt, vap);
	va_end(vap);
	if (eno) {
		fputc(':', stderr);
		fputc(' ', stderr);
		fputs(strerror(eno), stderr);
	}
	fputc('\n', stderr);
	return;
}

static size_t
ltostr(char *restrict buf, size_t bsz, long int v,
       int range, unsigned int pad)
{
#define C(x)	(char)((x) + '0')
	char *restrict bp = buf;
	const char *const ep = buf + bsz;
	bool negp;

	if (UNLIKELY((negp = v < 0))) {
		v = -v;
	} else if (!v) {
		*bp++ = C(0U);
		range--;
	}
	/* write the mantissa right to left */
	for (; v && bp < ep; range--) {
		register unsigned int x = v % 10U;

		v /= 10U;
		*bp++ = C(x);
	}
	/* fill up with padding */
	if (UNLIKELY(pad)) {
		static const char pads[] = " 0";
		const char p = pads[2U - pad];

		while (range-- > 0) {
			*bp++ = p;
		}
	}
	/* write the sign */
	if (UNLIKELY(negp)) {
		*bp++ = '-';
	}

	/* reverse the string */
	for (char *ip = buf, *jp = bp - 1; ip < jp; ip++, jp--) {
		register char tmp = *ip;
		*ip = *jp;
		*jp = tmp;
	}
#undef C
	return bp - buf;
}

static inline void
dt_io_warn_dur(const char *d1, const char *d2)
{
	error(0, "\
duration between `%s' and `%s' is not defined", d1, d2);
	return;
}

static long int
__strf_tot_secs(struct dt_dt_s dur)
{
	long int res;

	if (dur.typ == DT_SEXY) {
		res = dur.sexydur;
	} else if (dur.typ == DT_SEXYTAI) {
		res = dur.soft;
	} else {
		/* otherwise */
		res = dur.t.sdur;
	}
	return res;
}

static long int
__strf_tot_corr(struct dt_dt_s dur)
{
	if (dur.typ == DT_SEXYTAI) {
		return dur.corr;
	}
	/* otherwise no corrections */
	return 0;
}

static int
__strf_tot_days(struct dt_dt_s dur)
{
/* DUR expressed solely as the number of days */
	int d = 0;

	switch (dur.d.typ) {
	case DT_DAISY:
		d = dur.d.daisydur;
		break;
	case DT_BIZSI:
		d = dur.d.bizsidur;
		break;
	case DT_BIZDA:
		d = dur.d.bizda.bd;
		break;
	case DT_YMD:
		d = dur.d.ymd.d;
		break;
	case DT_YD:
		d = dur.d.yd.d;
		break;
	case DT_YMCW:
		d = dur.d.ymcw.w + dur.d.ymcw.c * (int)GREG_DAYS_P_WEEK;;
		break;
	case DT_YWD:
		d = dur.d.ywd.w + dur.d.ywd.c * (int)GREG_DAYS_P_WEEK;
		break;
	case DT_MD:
		d = dur.d.md.d;
		break;
	default:
		break;
	}
	return d;
}

static int
__strf_tot_mon(struct dt_dt_s dur)
{
/* DUR expressed as month and days */
	int m = 0;

	switch (dur.d.typ) {
	case DT_BIZDA:
		m = dur.d.bizda.m + dur.d.bizda.y * (int)GREG_MONTHS_P_YEAR;
		break;
	case DT_YMD:
		m = dur.d.ymd.m + dur.d.ymd.y * (int)GREG_MONTHS_P_YEAR;
		break;
	case DT_MD:
		m = dur.d.md.m;
		break;
	case DT_YMCW:
		m = dur.d.ymcw.m + dur.d.ymcw.y * (int)GREG_MONTHS_P_YEAR;
		break;
	case DT_YD:
		m = dur.d.yd.y * (int)GREG_MONTHS_P_YEAR;
		break;
	case DT_YWD:
		m = dur.d.ywd.y * (int)GREG_MONTHS_P_YEAR;
		break;
	default:
		break;
	}
	return m;
}

static int
__strf_ym_mon(struct dt_dt_s dur)
{
	return __strf_tot_mon(dur) % (int)GREG_MONTHS_P_YEAR;
}

static int
__strf_tot_years(struct dt_dt_s dur)
{
	return __strf_tot_mon(dur) / (int)GREG_MONTHS_P_YEAR;
}

static struct precalc_s {
	int Y;
	int m;
	int w;
	int d;
	int db;

	long int H;
	long int M;
	long int S;
	long int N;

	long int rS;
} precalc(durfmt_t f, struct dt_dt_s dur)
{
#define MINS_PER_DAY	(MINS_PER_HOUR * HOURS_PER_DAY)
#define SECS_PER_WEEK	(SECS_PER_DAY * GREG_DAYS_P_WEEK)
#define MINS_PER_WEEK	(MINS_PER_DAY * GREG_DAYS_P_WEEK)
#define HOURS_PER_WEEK	(HOURS_PER_DAY * GREG_DAYS_P_WEEK)
	struct precalc_s res = {0};

	/* date specs */
	if (f.has_year) {
		/* just years */
		res.Y = __strf_tot_years(dur);
	}
	if (f.has_year && f.has_mon) {
		/* years and months */
		res.m = __strf_ym_mon(dur);
	} else if (f.has_mon) {
		/* just months */
		res.m = __strf_tot_mon(dur);
	}
	if (f.has_day || f.has_week) {
		res.d = __strf_tot_days(dur);
		if (f.has_week) {
			/* week shadows days in the hierarchy */
			res.w = res.d / (int)GREG_DAYS_P_WEEK;
			res.d %= (int)GREG_DAYS_P_WEEK;
		}
	}

	/* time specs */
	if (f.has_sec || f.has_min || f.has_hour) {
		res.S = __strf_tot_secs(dur);

		/* carry from the date specs */
		res.S += res.w * (long int)SECS_PER_WEEK;
		res.S += res.d * (long int)SECS_PER_DAY;

		if (f.has_week) {
			res.w = res.S / (long int)SECS_PER_WEEK;
			if ((res.S %= (long int)SECS_PER_WEEK) < 0) {
				res.S += SECS_PER_WEEK;
				res.w--;
			}
		}
		if (f.has_day) {
			res.d = res.S / (long int)SECS_PER_DAY;
			if ((res.S %= (long int)SECS_PER_DAY) < 0) {
				res.S += SECS_PER_DAY;
				res.d--;
			}
		}
		if (f.has_hour) {
			res.H = res.S / (long int)SECS_PER_HOUR;
			res.S %= (long int)SECS_PER_HOUR;
		}
		if (f.has_min) {
			/* minutes and seconds */
			res.M = res.S / (long int)SECS_PER_MIN;
			res.S %= (long int)SECS_PER_MIN;
		}
	}
	return res;
}

static size_t
__strfdtdur(
	char *restrict buf, size_t bsz, const char *fmt,
	struct dt_dt_s dur, durfmt_t f)
{
/* like strfdtdur() but do some calculations based on F on the way there */
	static const char sexy_dflt_dur[] = "%0T";
	static const char ddur_dflt_dur[] = "%d";
	struct precalc_s pre;
	const char *fp;
	char *bp;

	if (UNLIKELY(buf == NULL || bsz == 0)) {
		bp = buf;
		goto out;
	}

	/* translate high-level format names */
	if (dur.typ == DT_SEXY) {
		if (fmt == NULL) {
			fmt = sexy_dflt_dur;
			f.has_sec = 1U;
		}
	} else if (dur.typ == DT_SEXYTAI) {
		if (fmt == NULL) {
			fmt = sexy_dflt_dur;
			f.has_sec = 1U;
		}
	} else if (dt_sandwich_p(dur)) {
		if (fmt == NULL) {
			fmt = sexy_dflt_dur;
			f.has_sec = 1U;
		} else {
			__trans_dtdurfmt(&fmt);
		}
	} else if (dt_sandwich_only_d_p(dur)) {
		if (fmt == NULL) {
			fmt = ddur_dflt_dur;
			f.has_day = 1U;
		} else {
			__trans_ddurfmt(&fmt);
			f.has_day = 1U;
		}
	} else if (dt_sandwich_only_t_p(dur)) {
		if (fmt == NULL) {
			fmt = sexy_dflt_dur;
			f.has_sec = 1U;
		}
	} else {
		bp = buf;
		goto out;
	}

	/* precompute */
	pre = precalc(f, dur);

	/* assign and go */
	bp = buf;
	fp = fmt;
	if (dur.neg) {
		*bp++ = '-';
	}
	for (char *const eo = buf + bsz; *fp && bp < eo;) {
		const char *fp_sav = fp;
		struct dt_spec_s spec = __tok_spec(fp_sav, &fp);

		if (spec.spfl == DT_SPFL_UNK) {
			/* must be literal then */
			*bp++ = *fp_sav;
		} else if (UNLIKELY(spec.rom)) {
			continue;
		}
		/* otherwise switch over spec.spfl */
		switch (spec.spfl) {
		case DT_SPFL_LIT_PERCENT:
			/* literal % */
			*bp++ = '%';
			break;
		case DT_SPFL_LIT_TAB:
			/* literal tab */
			*bp++ = '\t';
			break;
		case DT_SPFL_LIT_NL:
			/* literal \n */
			*bp++ = '\n';
			break;

		case DT_SPFL_N_DSTD:
			bp += ltostr(bp, eo - bp, pre.d, -1, DT_SPPAD_NONE);
			*bp++ = 'd';
			goto bizda_suffix;

		case DT_SPFL_N_DCNT_MON: {
			int rng = 2;

			if (!f.has_mon && !f.has_week && f.has_year) {
				rng++;
			}
			bp += ltostr(bp, eo - bp, pre.d, rng, spec.pad);
		}
		bizda_suffix:
			if (spec.bizda) {
				/* don't print the b after an ordinal */
				switch (__get_bizda_param(dur.d).ab) {
				case BIZDA_AFTER:
					*bp++ = 'b';
					break;
				case BIZDA_BEFORE:
					*bp++ = 'B';
					break;
				}
			}
			break;

		case DT_SPFL_N_WCNT_MON:
		case DT_SPFL_N_DCNT_WEEK:
			bp += ltostr(bp, eo - bp, pre.w, 2, spec.pad);
			break;

		case DT_SPFL_N_MON:
			bp += ltostr(bp, eo - bp, pre.m, 2, spec.pad);
			break;

		case DT_SPFL_N_YEAR:
			bp += ltostr(bp, eo - bp, pre.Y, -1, DT_SPPAD_NONE);
			break;

			/* time specs */
		case DT_SPFL_N_TSTD:
			if (UNLIKELY(spec.tai)) {
				pre.S += __strf_tot_corr(dur);
			}
			bp += ltostr(bp, eo - bp, pre.S, -1, DT_SPPAD_NONE);
			*bp++ = 's';
			break;

		case DT_SPFL_N_SEC:
			if (UNLIKELY(spec.tai)) {
				pre.S += __strf_tot_corr(dur);
			}

			bp += ltostr(bp, eo - bp, pre.S, 2, spec.pad);
			break;

		case DT_SPFL_N_MIN:
			bp += ltostr(bp, eo - bp, pre.M, 2, spec.pad);
			break;

		case DT_SPFL_N_HOUR:
			bp += ltostr(bp, eo - bp, pre.H, 2, spec.pad);
			break;

		default:
			break;
		}
	}
out:
	if (bp < buf + bsz) {
		*bp = '\0';
	}
	return bp - buf;
}

static int
ddiff_prnt(struct dt_dt_s dur, const char *fmt, durfmt_t f)
{
/* this is mainly a better dt_strfdtdur() */
	char buf[256];
	size_t res = __strfdtdur(buf, sizeof(buf), fmt, dur, f);

	if (res > 0 && buf[res - 1] != '\n') {
		/* auto-newline */
		buf[res++] = '\n';
	}
	if (res > 0) {
		__io_write(buf, res, stdout);
	}
	return (res > 0) - 1;
}


#if defined __INTEL_COMPILER
# pragma warning (disable:593)
# pragma warning (disable:181)
#elif defined __GNUC__
# pragma GCC diagnostic ignored "-Wswitch-enum"
# pragma GCC diagnostic ignored "-Wunused-function"
#endif	/* __INTEL_COMPILER */
#include "ddiff.xh"
#include "ddiff.x"
#if defined __INTEL_COMPILER
# pragma warning (default:593)
# pragma warning (default:181)
#elif defined __GNUC__
# pragma GCC diagnostic warning "-Wswitch-enum"
# pragma GCC diagnostic warning "-Wunused-function"
#endif	/* __INTEL_COMPILER */

int
main(int argc, char *argv[])
{
	struct gengetopt_args_info argi[1];
	struct dt_dt_s d;
	const char *ofmt;
	const char *refinp;
	char **fmt;
	size_t nfmt;
	int res = 0;
	durfmt_t dfmt;
	dt_dttyp_t dtyp;
	zif_t fromz = NULL;

	if (cmdline_parser(argc, argv, argi)) {
		res = 1;
		goto out;
	}
	/* unescape sequences, maybe */
	if (argi->backslash_escapes_given) {
		dt_io_unescape(argi->format_arg);
	}

	/* try and read the from and to time zones */
	if (argi->from_zone_given) {
		fromz = zif_open(argi->from_zone_arg);
	}

	ofmt = argi->format_arg;
	fmt = argi->input_format_arg;
	nfmt = argi->input_format_given;

	if (argi->inputs_num == 0 ||
	    (refinp = argi->inputs[0],
	     dt_unk_p(d = dt_io_strpdt(refinp, fmt, nfmt, fromz)) &&
	     dt_unk_p(d = dt_io_strpdt(refinp, NULL, 0U, fromz)))) {
		error(0, "Error: reference DATE must be specified\n");
		cmdline_parser_print_help();
		res = 1;
		goto out;
	}

	/* try and guess the diff tgttype most suitable for user's FMT */
	dfmt = determine_durfmt(ofmt);

	if (argi->inputs_num > 1) {
		for (size_t i = 1; i < argi->inputs_num; i++) {
			struct dt_dt_s d2;
			struct dt_dt_s dur;
			const char *inp = argi->inputs[i];

			d2 = dt_io_strpdt(inp, fmt, nfmt, fromz);
			if (dt_unk_p(d2)) {
				if (!argi->quiet_given) {
					dt_io_warn_strpdt(inp);
				}
				continue;
			}
			/* guess the diff type */
			if ((dtyp = determine_durtype(d, d2, dfmt)) == DT_UNK) {
				if (!argi->quiet_given) {
				        dt_io_warn_dur(refinp, inp);
				}
				continue;
			}
			/* subtraction and print */
			dur = dt_dtdiff(dtyp, d, d2);
			ddiff_prnt(dur, ofmt, dfmt);
		}
	} else {
		/* read from stdin */
		size_t lno = 0;
		void *pctx;

		/* no threads reading this stream */
		__io_setlocking_bycaller(stdout);

		/* using the prchunk reader now */
		if ((pctx = init_prchunk(STDIN_FILENO)) == NULL) {
			error(errno, "Error: could not open stdin");
			goto out;
		}
		while (prchunk_fill(pctx) >= 0) {
			for (char *line; prchunk_haslinep(pctx); lno++) {
				struct dt_dt_s d2;
				struct dt_dt_s dur;

				(void)prchunk_getline(pctx, &line);
				d2 = dt_io_strpdt(line, fmt, nfmt, fromz);

				if (dt_unk_p(d2)) {
					if (!argi->quiet_given) {
						dt_io_warn_strpdt(line);
					}
					continue;
				}
				/* guess the diff type */
				dtyp = determine_durtype(d, d2, dfmt);
				if (dtyp == DT_UNK) {
					if (!argi->quiet_given) {
						dt_io_warn_dur(refinp, line);
					}
					continue;
				}
				/* perform subtraction now */
				dur = dt_dtdiff(dtyp, d, d2);
				ddiff_prnt(dur, ofmt, dfmt);
			}
		}
		/* get rid of resources */
		free_prchunk(pctx);
	}

	if (argi->from_zone_given) {
		zif_close(fromz);
	}

out:
	cmdline_parser_free(argi);
	return res;
}

/* ddiff.c ends here */
