// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Auxiliary latitude conversions
/**
\file
\author Steven Ward
\sa https://geographiclib.sourceforge.io/html/auxlat.html
*/

// Generated by "generate-series-approx-coeff-aux-lat.cal" on (@1657571387) Mon Jul 11 15:29:47 2022

#pragma once

#include "angle.hpp"
#include "ellipsoid-wgs84.hpp"

#include <cmath>
#include <concepts>
#include <valarray>

template <std::floating_point T>
const std::valarray<T> iota_0_1{0, 1, 2, 3, 4, 5, 6, 7, };

template <std::floating_point T>
const std::valarray<T> iota_0_2{0, 2, 4, 6, 8, 10, 12, 14, };

template <std::floating_point T>
const std::valarray<T> iota_1_1{1, 2, 3, 4, 5, 6, 7, 8, };

template <std::floating_point T>
const std::valarray<T> iota_1_2{1, 3, 5, 7, 9, 11, 13, 15, };

template <std::floating_point T>
const std::valarray<T> iota_2_2{2, 4, 6, 8, 10, 12, 14, 16, };

template <angle_unit U, std::floating_point T>
auto
parametric_from_geodetic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-1.679220386383704695103145345551967249688658059607459169650438630960777905e-3L},
		T{1.409890553023319244294730683493976693942553448022341346110792683876616471e-6L},
		T{-1.578344639471035488788295761936389311404425500771441879578772747653400950e-9L},
		T{1.987791371504400973469023663829258875915788668034097311348322838438480461e-12L},
		T{-2.670351835926251588399351176320141990638042478265660777188811026149621152e-15L},
		T{3.736757701420429497356065312943204039684461855248898415438970290471179848e-18L},
		T{-5.378434038172712437143337804843453107992200395108675254630717192861650381e-21L},
		T{7.902629073254694892851741383091419871504236473897932239569560067395274317e-24L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geodetic_from_parametric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{1.679220386383704695103145345551967249688658059607459169650438630960777905e-3L},
		T{1.409890553023319244294730683493976693942553448022341346110792683876616471e-6L},
		T{1.578344639471035488788295761936389311404425500771441879578772747653400950e-9L},
		T{1.987791371504400973469023663829258875915788668034097311348322838438480461e-12L},
		T{2.670351835926251588399351176320141990638042478265660777188811026149621152e-15L},
		T{3.736757701420429497356065312943204039684461855248898415438970290471179848e-18L},
		T{5.378434038172712437143337804843453107992200395108675254630717192861650381e-21L},
		T{7.902629073254694892851741383091419871504236473897932239569560067395274317e-24L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geocentric_from_geodetic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-3.358431302726276007054543942795382272797919844759950623541450865535504434e-3L},
		T{5.639530407565855678246222003201630716382705967048445689404015175829190467e-6L},
		T{-1.262665030229723147251817391440411551969824523256753085445126605730480194e-8L},
		T{3.180430321785992051771413480471065670965406333908880875897262159053006136e-11L},
		T{-8.545005398041550014119331753457625876692116905161264052678491555613667584e-14L},
		T{2.391484467448219814270030399367769157328313485668548628467874389754010039e-16L},
		T{-6.884395568861071919543472390199619978230016505739104325927318006862912488e-19L},
		T{2.023073042753201892570045794071403487105084537317870653329807377253190225e-21L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geodetic_from_geocentric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{3.358431302726276007054543942795382272797919844759950623541450865535504434e-3L},
		T{5.639530407565855678246222003201630716382705967048445689404015175829190467e-6L},
		T{1.262665030229723147251817391440411551969824523256753085445126605730480194e-8L},
		T{3.180430321785992051771413480471065670965406333908880875897262159053006136e-11L},
		T{8.545005398041550014119331753457625876692116905161264052678491555613667584e-14L},
		T{2.391484467448219814270030399367769157328313485668548628467874389754010039e-16L},
		T{6.884395568861071919543472390199619978230016505739104325927318006862912488e-19L},
		T{2.023073042753201892570045794071403487105084537317870653329807377253190225e-21L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geocentric_from_parametric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-1.679220386383704695103145345551967249688658059607459169650438630960777905e-3L},
		T{1.409890553023319244294730683493976693942553448022341346110792683876616471e-6L},
		T{-1.578344639471035488788295761936389311404425500771441879578772747653400950e-9L},
		T{1.987791371504400973469023663829258875915788668034097311348322838438480461e-12L},
		T{-2.670351835926251588399351176320141990638042478265660777188811026149621152e-15L},
		T{3.736757701420429497356065312943204039684461855248898415438970290471179848e-18L},
		T{-5.378434038172712437143337804843453107992200395108675254630717192861650381e-21L},
		T{7.902629073254694892851741383091419871504236473897932239569560067395274317e-24L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
parametric_from_geocentric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{1.679220386383704695103145345551967249688658059607459169650438630960777905e-3L},
		T{1.409890553023319244294730683493976693942553448022341346110792683876616471e-6L},
		T{1.578344639471035488788295761936389311404425500771441879578772747653400950e-9L},
		T{1.987791371504400973469023663829258875915788668034097311348322838438480461e-12L},
		T{2.670351835926251588399351176320141990638042478265660777188811026149621152e-15L},
		T{3.736757701420429497356065312943204039684461855248898415438970290471179848e-18L},
		T{5.378434038172712437143337804843453107992200395108675254630717192861650381e-21L},
		T{7.902629073254694892851741383091419871504236473897932239569560067395274317e-24L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
rectifying_from_geodetic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-2.518827916120229661657571908925508424605064891405302067262333362680973469e-3L},
		T{2.643541059811379927544469746431585917134313641675319133888056941995059410e-6L},
		T{-3.452623422537344359635229824141300744034192139507824791029317672262246097e-9L},
		T{4.891822051979845598224338262767554434092057242257728259799192354298205884e-12L},
		T{-7.228713128706845522586899579681238232669082338545266931909720759455272018e-15L},
		T{1.095845999609210470993711907654894692759540009707788879715394836937240196e-17L},
		T{-1.689952296662177955713739197957403356930166481568570569509212164846910166e-20L},
		T{2.638269370937186730357410426645769887827166592596631766808203196938189801e-23L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geodetic_from_rectifying_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{2.518826584397703260574823667286061472986548058820741864868281243564339943e-3L},
		T{3.700949035657531029216015934681439976415587062100466269118884427347486559e-6L},
		T{7.447770270137701513284644362243130791896861142761211878981539988077534998e-9L},
		T{1.703585711324716665090804980250143434126167249503692778269459716141994478e-11L},
		T{4.178119473101992618457516714020959619491678065272472903923182093457418729e-14L},
		T{1.070629970398244280985182120137954897098935028130114338968789414161286004e-16L},
		T{2.827354971632038690729454917602911339505169731806998192015611605609237440e-19L},
		T{7.632152024551398994876113719373407402757802702139546104028797836122699383e-22L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
rectifying_from_parametric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-8.396093053734098872191906363085028082016882971351006890874444542269911563e-4L},
		T{-1.762360706540919951696313164287723944756209094450212755925371294663372940e-7L},
		T{-9.864638350106698170386370926118002125811977541450927974369479063606417419e-11L},
		T{-7.764796907904516822578314702805641958876281336917028983808241832219374419e-14L},
		T{-7.301730433037217699582726848162866901685941756106330234252243191368961634e-17L},
		T{-7.663258738525947349606376976607655194122657410543978179827935922638043328e-20L},
		T{-8.666422034165015157506354861320017215026494777274720869278011101779026494e-23L},
		T{-1.034615439583210482493102128096380348167516310822208536003216939975760706e-25L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
parametric_from_rectifying_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{8.396088614653447644415225877354812603859448486326600549697587791820493460e-4L},
		T{8.811785311351842547837432080476483328684935329225646255915231396917238910e-7L},
		T{1.430367006250896601410221276258503672615306592924279951779919443836156374e-9L},
		T{2.790134135801120685210435913373203395311969709920316588176591706192546353e-12L},
		T{6.027357596195136482450347865921393484215801389901383078839589509158501489e-15L},
		T{1.389627089890374481604907931459321275674016950980412515838258938422400527e-17L},
		T{3.351928390882417499702699885061976523608122014087605318703877888132101000e-20L},
		T{8.358067425220662600691536733474567172685058915892148514398736258108542449e-23L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
rectifying_from_geocentric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{8.396140404006524304422340504896072158359396001134271780470931891499494626e-4L},
		T{-1.762281195068226313531023507818350007787746140834977912574329668419665574e-7L},
		T{-1.479679897356099405948262436668845754689964464739596010270338345725216441e-9L},
		T{-4.053188673731637003138647485424903064765586371510958387497885466874240016e-12L},
		T{-9.606906036712612319088462767807573822455424932911646710496655834659456894e-15L},
		T{-2.202982774169971907129736060494628625715535805502209590832520877813987590e-17L},
		T{-5.063028799899009915805000465799654905711993721547858898145781091854480357e-20L},
		T{-1.183959404842395352256238140409593292363957913497418940646571739528205885e-22L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geocentric_from_rectifying_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-8.396135964931436310617616748183589366506882765931615833934873464694238805e-4L},
		T{8.811811815283505213387802099115440070320458400804041115474410497426892307e-7L},
		T{1.479617780597923681011874281119216601779831768563537567251085314845169791e-10L},
		T{1.464949043194078909057404837513114719634762770395142058983381019631767189e-12L},
		T{2.261762154077190135370960698742266591424581689096064481386984485236370012e-15L},
		T{6.235981812797165725459172260555041572556139507479308404308993006103669827e-18L},
		T{1.445242593685691900613949068476780480265129640403856334189405024771844978e-20L},
		T{3.727738301257413244870934572494781964045061789057964228672369322191555381e-23L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
conformal_from_geodetic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-3.356554619797427643982037847336982452729334241061125988991070817474129181e-3L},
		T{4.694573027162541940489015604872118844966904884868718945257344108583232828e-6L},
		T{-8.194497547094186782334869697414202014703685475995073467901176757876416976e-9L},
		T{1.557996708850208041056757081964470393464955744915296939073350735197417982e-11L},
		T{-3.103285402796183053936110837391691736289323898489839679130453816009308205e-14L},
		T{6.369892404732840058022232839751829116618389638059891993468993185845213636e-17L},
		T{-1.335864665505359097463110696104235413605124744846562812722517630341622623e-19L},
		T{2.858958503143029371213326806666976943881376384382065015248812423149673961e-22L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geodetic_from_conformal_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{3.356551469132832188807318066526754851966145918719852861636092245702550671e-3L},
		T{6.571873198627697076746495453061696405846850948337450139392942542070618555e-6L},
		T{1.764640411334326361830920695374983813153504709031261471529878299392564131e-8L},
		T{5.387754068401978354109853498381992050334360116141134375813673733701371547e-11L},
		T{1.763982904963393368851521365550645654048984360995070164437495040192600107e-13L},
		T{6.034535706104789293366606752475821083838495471289242488334506160540506213e-16L},
		T{2.127574492567203130729048841886376545901773961825129357104125958583285448e-18L},
		T{7.703944663959872526572849359279674266183413933750368597966605805978690665e-21L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
conformal_from_parametric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-1.677340535134752029995991687057318537536440015518847313879899669824425629e-3L},
		T{4.680728584666731248705387220198565545120962052166228202899911764189241663e-7L},
		T{-3.144601146543696136963023816470494214730232925248657289702135920692831628e-10L},
		T{1.062637041528676714257637982476663981008729319536187874546402581080246017e-13L},
		T{-1.265179815490228580998254444647149025628206661641834113765183666129820854e-16L},
		T{1.013511833900621959855547873957375191650854399575598088478551667936900366e-20L},
		T{-8.309973345530973718838185822128283258733451102968902735827698737671350831e-23L},
		T{-3.801224080178771360082768738403554101278162004344916270909774840043870538e-26L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
parametric_from_conformal_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{1.677338960678219643003356172283507033110603884151849527611574271594785018e-3L},
		T{2.345392070911135060319137083576264462147966991843839751563698277300375857e-6L},
		T{5.037807416633439767273326891084239098949051410589516392005933127480738901e-9L},
		T{1.301470145949734968186139064242075427484770331440262107572808940134708540e-11L},
		T{3.728489326586954154042679262050566640618522433432214136499023201067511211e-14L},
		T{1.141270020175250969854480251204761191360596887160312023353894408455717627e-16L},
		T{3.658031412643262104940135300016195871538119774074898648085863562692005173e-19L},
		T{1.219720930443990710649749356603257185390309239692408675786657251363190561e-21L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
conformal_from_geocentric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{1.883008988902105115634932411555270305581377076771667947673454350965246161e-6L},
		T{-9.386567630606516562457947566169501020734896050515084768005768993676527535e-7L},
		T{-1.893846346689200674735576739420068326133000982844184751484220367343894579e-9L},
		T{-3.472748057723060296757548619412921233856256232876474734753128887903148765e-12L},
		T{-6.534067487264546109897587340466461358089690362002751125575333919410386459e-15L},
		T{-1.299547408001785681050339973732571642544715286106835656666479153515187519e-17L},
		T{-2.750495536678918703571786943351663353383726228786471618859644786726562383e-20L},
		T{-6.167344299040605313986609596665741441823784100729029735449226909486390983e-23L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geocentric_from_conformal_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-1.883007223175661126996924861505467396913388005463017098032289990209869217e-6L},
		T{9.386603158942903230312022407949941191871484387728681065478658430074071922e-7L},
		T{1.888543866297039756849773781233773155890433105968447985319139648509138564e-9L},
		T{5.220663304738262866877740833145900985730526054569761099728315852157933720e-12L},
		T{1.536907557736595928484340039016804504624552159879896092814455336429862864e-14L},
		T{4.808197546870842717445164878400317804100960506758279093640480741068312217e-17L},
		T{1.566338224023674833784430085255124341908773804954708422571994017375697690e-19L},
		T{5.290267049984951355388579442524977694369840540362186403404284597030199131e-22L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
conformal_from_rectifying_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-8.377321640579486770657418913059200983218978870438314865929985343944964181e-4L},
		T{-5.905870152220365182381321247563043463036556543367492227439814246595370513e-8L},
		T{-1.673482665343824644750109635834450014277184027650867038540694407629776733e-10L},
		T{-2.164798110490642057094907204554443387343897221775671858742550913478598090e-13L},
		T{-3.787930968626020095777796264207238741263402882648482625478508769316432166e-16L},
		T{-7.236769021815622217308585355095375284174722605236857917014426232835004284e-19L},
		T{-1.493479824778106994581824006185656820009334768069431393815925734442144253e-21L},
		T{-3.259522545838158127721946735097342101898835895074807799391343039224176127e-24L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
rectifying_from_conformal_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{8.377318206244698303199077626080242042703583655146908227548697589238827982e-4L},
		T{7.608527773572489157977417061771566101179882517867271594131863799986543498e-7L},
		T{1.197645503242491787067109441494542885414600965885537228666415648124690112e-9L},
		T{2.429170680397090550679591120912956095302552291047727118661009537694300577e-12L},
		T{5.711818370428018957007593465004486515893142446788420217554301009426179272e-15L},
		T{1.479997931379663185530900465470343831923222495104127727157967899016435575e-17L},
		T{4.107624109370719472100685408646518732946974530015223385953357854034360312e-20L},
		T{1.210785038922578447834763539123898596676178376927243251988347673103006509e-22L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
authalic_from_geodetic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-2.239209838678639798192057939967265666077159392412692521516962853316156436e-3L},
		T{2.130860651325022267416755583141937253442666420388367841819128785554044090e-6L},
		T{-2.559257686419122534263001522170227205643992580806094239067838498790400592e-9L},
		T{3.370196525542271482169126931044407079255688254600241957972993367928447836e-12L},
		T{-4.667543015630067367674318358414041227577026278727126452606944631023352338e-15L},
		T{6.676288281565181242414199552696476352899766277626770688204342510512890896e-18L},
		T{-9.768152202993309139613939667743016899962691985873896756579737840080837990e-21L},
		T{1.453210503805397031091791268146314807327933928107062934425578023334164655e-23L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geodetic_from_authalic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{2.239208996354166478743660250970973010317953787194409587151223517040056145e-3L},
		T{2.883197804860772041439701928135197116812640376372194257747864836838966323e-6L},
		T{5.086220740008021724658460963492072704511995794187719962224446280738178242e-9L},
		T{1.020181232035134888369273551947910838514231730799240537238254822402573655e-11L},
		T{2.194475077393880913017750309655700483366633179193376318972036879249140846e-14L},
		T{4.932746955654038349494923730071310913414150231485117246489122681751538280e-17L},
		T{1.142805261980944901869888147298816411890110240162898154585523070845027204e-19L},
		T{2.703327104718474583741266779974132802579254896007203275847026545937611358e-22L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
authalic_from_parametric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-5.599902945841022662669978411229049362271992477910025606067350351740980348e-4L},
		T{-2.193761449878500208187200311652502310808555816643810401446796758675078905e-7L},
		T{-1.386257721826785487794904839291343437961427552305007938994250673832206571e-10L},
		T{-1.117382504176188190775309235150519982188125342237962537455727366385491280e-13L},
		T{-1.047976779290969069256648240059062119551342252882355036662523653863713851e-16L},
		T{-1.089381937014874098281299865982540758436708130803004191124250060687354776e-19L},
		T{-1.219043322006157896935423843631032369570195977589376339476439504857510715e-22L},
		T{-1.441997446605881224395357482494732813808197645599530978093186198210721652e-25L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
parametric_from_authalic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{5.599900839321373631999370629850341526846562115211197949228532279348400442e-4L},
		T{5.329647134647360137478253975487235294425099472193002632510641601163066150e-7L},
		T{7.705802061419577992221684039069425812863632615610704865546256096882295449e-10L},
		T{1.331089713251716087729822407239646423152692051270624222593701196922670891e-12L},
		T{2.539373133728896910613181166334310131753053479773256061892782814177145919e-15L},
		T{5.162218783803971562652628386246088625772048589059362237062762772618292487e-18L},
		T{1.096829235957873547005952972891671740512529702418429438012855598263929545e-20L},
		T{2.403728233020553143387073593785660768553492286830670548748233055047934429e-23L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
authalic_from_geocentric_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{1.119232407608194381757816949798131936182562187064302227546707277833501468e-3L},
		T{2.501731134733395355836989101275207274984816927095879336925168085828267086e-7L},
		T{-8.760780212183074487100312816460592734135352617959536892703178292850103581e-10L},
		T{-3.329608544844697618156772978906728984516834971920683273717183176018549779e-12L},
		T{-9.137829324152152405340533249053303038684848980314423578986446802533482607e-15L},
		T{-2.316487541738103954765804219448912059740125528429161787946884009583684505e-17L},
		T{-5.751860171347359910235569939413212065333975608617906541686777331433704148e-20L},
		T{-1.429701973148232470442665685629981999270331160544017521040886330790274943e-22L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
geocentric_from_authalic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-1.119231986588554210194244171907306909055342446906150762382317224902655732e-3L},
		T{1.002509191109325314069880162399391495793397133003342327987016932466547989e-6L},
		T{-3.869756633763778426833036248692419441411007859077981799371174708242890761e-10L},
		T{1.210112260975685988035418800190199759364517125451408458189014677502460394e-12L},
		T{4.113341537737138150982237109657774259822745886645139140427852291909484424e-16L},
		T{2.965033695079247795378605102110700058171912277872937262692232955461943247e-18L},
		T{4.077802000045611681521324709700288643425030406543099979673069675137509828e-21L},
		T{1.164547132689385934837557031276255525054897765087137484932046778382090648e-23L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
authalic_from_rectifying_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{2.796190339519183506434663455787257652470102899489069761219386174849672223e-4L},
		T{1.916306783468745837680505450207478370940995322427904261684130016312209117e-7L},
		T{2.325315230665301347896404982043842625206601121813766440481894545147431232e-10L},
		T{3.627750656259158862718951533550152149222482500175275664953689796574141551e-13L},
		T{6.532751830775718177484946612817359277945986193389635880907001333736759663e-16L},
		T{1.291422728370687644380721169560569264376946113177528810348572257036385873e-18L},
		T{2.726308730822011267689113589038759534285698390791950948643409450971391767e-21L},
		T{6.059121300253660715448548830764391876873410677843085586817784221021330838e-24L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
rectifying_from_authalic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-2.796190766042863120760603474806650878118547830240335393869566961638430655e-4L},
		T{-1.134439524582115731224167421244100966904139291490456145727442077247444615e-7L},
		T{-1.045746908384427905522538494565277473766912136946205357286931283070831800e-10L},
		T{-1.328118775794541731174990497721117636780162258092700311721446770474474968e-13L},
		T{-2.005163426007800885270966453068570721935249399629324066786246927010271053e-16L},
		T{-3.374619222981070642395856602548902050863530786004681358741264199600820049e-19L},
		T{-6.119547798315263786227689705048115636792843625185581034822624541230351888e-22L},
		T{-1.172839311524411277142738782696646342325170753529518288502490152004362325e-24L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
authalic_from_conformal_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{1.117350451902692205713455512200660119422231902621780441439992461707408389e-3L},
		T{1.186728019394944551019515651526417762578884108034388003338203813109391326e-6L},
		T{2.062110053835649672443882186806551056350690478564979140089575053215504567e-9L},
		T{4.477417057778599931765946487663935788465110030601697553449882443357219097e-12L},
		T{1.106472092029794612318688760918344075213978486356719131701197067614767096e-14L},
		T{2.977524014052006474013528858113312699514250359260636816821627429249921569e-17L},
		T{8.512918134195507481750166686443128228705230318061027018140758675030179093e-20L},
		T{2.568869096119654398681234105149233098932578494266610709875542829253739760e-22L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
auto
conformal_from_authalic_approx(const angle<U, T>& a)
{
	static const std::valarray<T> coeff{
		T{-1.117351080405140321665516728862431169436813180379900485964963520759892042e-3L},
		T{6.174325291234760778814967655817887697999575976885015709023431062422711111e-8L},
		T{-1.766091997652511176921568490330888776717017723212757427734471260589457232e-10L},
		T{-1.406616314757248915510174104943432044627398266770726262291946301681727632e-13L},
		T{-2.476520979060303451055906271827413453017733641632115994587583806455784462e-16L},
		T{-4.068930766433071000462171353491021505222306895549256081036992840205372084e-19L},
		T{-7.460625947711127545861491502676630934512650764792891425341924258244860275e-22L},
		T{-1.431305838145303992305135215044904796067986891106095772555594883706648733e-24L},
	};

	return a + ang_rad<T>{(coeff * std::sin(iota_2_2<T> * a.to_rad())).sum()};
}

template <angle_unit U, std::floating_point T>
constexpr auto
geocentric_from_geodetic_exact(const angle<U, T>& a)
{
#if 0
	// This is not as accurate.
	const auto s = sin(a);
	const auto c = cos(a);
	return a_atan2(s * (1 - WGS84<T>.e2), c);
#else
	return a_atan(tan(a) * (1 - WGS84<T>.e2));
#endif
}

template <angle_unit U, std::floating_point T>
constexpr auto
geodetic_from_geocentric_exact(const angle<U, T>& a)
{
#if 0
	// This is not as accurate.
	const auto s = sin(a);
	const auto c = cos(a);
	return a_atan2(s, c * (1 - WGS84<T>.e2));
#else
	return a_atan(tan(a) / (1 - WGS84<T>.e2));
#endif
}

template <angle_unit U, std::floating_point T>
constexpr auto
parametric_from_geodetic_exact(const angle<U, T>& a)
{
#if 0
	// This is not as accurate.
	const auto s = sin(a);
	const auto c = cos(a);
	return a_atan2(s * (1 - WGS84<T>.f), c);
#else
	return a_atan(tan(a) * (1 - WGS84<T>.f));
#endif
}

template <angle_unit U, std::floating_point T>
constexpr auto
geodetic_from_parametric_exact(const angle<U, T>& a)
{
#if 0
	// This is not as accurate.
	const auto s = sin(a);
	const auto c = cos(a);
	return a_atan2(s, c * (1 - WGS84<T>.f));
#else
	return a_atan(tan(a) / (1 - WGS84<T>.f));
#endif
}

template <angle_unit U, std::floating_point T>
constexpr auto
geocentric_from_parametric_exact(const angle<U, T>& a)
{
#if 0
	// This is not as accurate.
	const auto s = sin(a);
	const auto c = cos(a);
	return a_atan2(s * (1 - WGS84<T>.f), c);
#else
	return a_atan(tan(a) * (1 - WGS84<T>.f));
#endif
}

template <angle_unit U, std::floating_point T>
constexpr auto
parametric_from_geocentric_exact(const angle<U, T>& a)
{
#if 0
	// This is not as accurate.
	const auto s = sin(a);
	const auto c = cos(a);
	return a_atan2(s, c * (1 - WGS84<T>.f));
#else
	return a_atan(tan(a) / (1 - WGS84<T>.f));
#endif
}
