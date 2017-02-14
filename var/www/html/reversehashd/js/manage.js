$(document).ready(function(){
	reversehashd.initWebsocket();
	reversehashd.ready(function(){
		loadStatistics();
	});

	$('#statistics').unbind().bind('click', function(){
		loadStatistics();
	});
	
	$('#training').unbind().bind('click', function(){
		console.log("TODO");
	});
	
	$('#visualize').unbind().bind('click', function(){
		console.log("TODO");
	});
	
	$('#state').unbind().bind('click', function(){
		console.log("TODO");
	});
});

function loadStatistics(){
	reversehashd.statistics().done(function(r){
		// console.log(r);
		$('.content').html('<div class="statistics-table"></div>');
		$('.statistics-table').append(''
			+ '<div class="statistics-row">'
			+ '		<div class="statistics-cell">Modified</div>'
			+ '		<div class="statistics-cell">Name</div>' 
			+ '		<div class="statistics-cell">Last Success Percent</div>'
			+ '		<div class="statistics-cell">Training</div>'
			+ '		<div class="statistics-cell">Info</div>'
			+ '</div>');
		
		for(var i = 0; i < r.statistics.length; i++){
			var sbit = r.statistics[i];
			$('.statistics-table').append(''
			+ '<div class="statistics-row" id="' + sbit.name + '">'
			+ '		<div class="statistics-cell modified">' + sbit.modified + '</div>'
			+ '		<div class="statistics-cell name p' + sbit.lp + '">' + sbit.name + '</div>' 
			+ '		<div class="statistics-cell lp p' + sbit.lp + '">' + sbit.lp + ' %</div>'
			+ '		<div class="statistics-cell"> <div class="bittraining" bitid="' + sbit.name + '">start</div></div>'
			+ '		<div class="statistics-cell info"></div>'
			+ '</div>');
		}
		
		$('.bittraining').unbind().bind('click',function(){
			var bitid = $(this).attr('bitid');
			reversehashd.training(bitid);
		});
		
	}).fail(function(r){
		console.fail(r);
		$('.content').html('failed');
	});
}


function showLoading(){
	$('.inputform').css({'opacity': 0});
	setTimeout(function(){
		$('.background').show();
		$('.background').css({'opacity': 1});
		$('.inputform').hide();
	},1000);
}

function hideLoading(){
	$('.background').css({'opacity': 0});
	setTimeout(function(){
		$('.background').hide();
		$('.inputform').show();
		$('.inputform').css({'opacity': 1});
	},1000);
}