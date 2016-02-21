var MenuView = Backbone.View.extend({

    initialize:function(){
        var view = this;
        this.$el.find("li a").click(function(){
            var $a = $(this);
            $a.parent().parent().find(".active").removeClass("active");
            $a.parent().addClass("active");
            view.trigger("change", $a.attr("rel")||$a.html());
        });
    },
    select:function(index){
        this.$el.find("li a:eq("+index+")").click();
    }
});
